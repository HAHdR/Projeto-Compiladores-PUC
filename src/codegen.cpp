#include "ast.h"
#include <iostream>
#include <llvm/IR/Verifier.h>

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext);
std::unique_ptr<llvm::Module> TheModule;
std::map<std::string, llvm::AllocaInst*> NamedValues;

// Função auxiliar para criar alocação de memória na pilha (stack)
static llvm::AllocaInst* CreateEntryBlockAlloca(llvm::Function *TheFunction, const std::string &VarName) {
    llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(llvm::Type::getInt32Ty(TheContext), nullptr, VarName);
}

llvm::Value* NumberAST::codegen() {
    // Retorna uma constante inteira de 32 bits
    return llvm::ConstantInt::get(TheContext, llvm::APInt(32, Val, true));
}

llvm::Value* StringAST::codegen() {
    // Cria uma string global no módulo LLVM (SEM quebra de linha embutida —
    // quem decide se imprime com '\n' no final é o write/writeln que a chamou)
    return Builder.CreateGlobalStringPtr(Str);
}

llvm::Value* VariableAST::codegen() {
    llvm::Value* V = NamedValues[Name];
    if (!V) {
        std::cerr << "Erro: variável '" << Name << "' usada antes de ser inicializada." << std::endl;
        return nullptr;
    }
    // Carrega (load) o valor de 32 bits guardado nessa variável
    return Builder.CreateLoad(llvm::Type::getInt32Ty(TheContext), V, Name.c_str());
}

llvm::Value* CallExprAST::codegen() {
    // 1. Procura a função/procedimento declarado no módulo LLVM
    llvm::Function* CalleeF = TheModule->getFunction(Callee);
    if (!CalleeF) {
        std::cerr << "Erro: função/procedimento '" << Callee << "' não foi declarado." << std::endl;
        return nullptr;
    }

    // 2. Confere se a quantidade de argumentos bate com a assinatura
    if (CalleeF->arg_size() != Args.size()) {
        std::cerr << "Erro: '" << Callee << "' espera " << CalleeF->arg_size()
                   << " argumento(s), mas recebeu " << Args.size() << "." << std::endl;
        return nullptr;
    }

    // 3. Gera o código de cada argumento, na ordem
    std::vector<llvm::Value*> ArgsV;
    for (auto &Arg : Args) {
        llvm::Value* V = Arg->codegen();
        if (!V) return nullptr;
        ArgsV.push_back(V);
    }

    // 4. Chama a função. Procedimentos (retorno void) não recebem nome de
    //    registrador — não dá para nomear um valor que não existe.
    if (CalleeF->getReturnType()->isVoidTy()) {
        return Builder.CreateCall(CalleeF, ArgsV);
    }
    return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

llvm::Value* BinaryExprAST::codegen() {
    llvm::Value* L = LHS->codegen();
    llvm::Value* R = RHS->codegen();
    if (!L || !R) return nullptr;

    switch (Op) {
        case BinOp::ADD: return Builder.CreateAdd(L, R, "addtmp");
        case BinOp::SUB: return Builder.CreateSub(L, R, "subtmp");
        case BinOp::MUL: return Builder.CreateMul(L, R, "multmp");
        case BinOp::DIV: return Builder.CreateSDiv(L, R, "divtmp");
        case BinOp::LT:  return Builder.CreateICmpSLT(L, R, "lttmp");
        case BinOp::GT:  return Builder.CreateICmpSGT(L, R, "gttmp");
        case BinOp::EQ:  return Builder.CreateICmpEQ(L, R, "eqtmp");
        case BinOp::AND: return Builder.CreateAnd(L, R, "andtmp");
        case BinOp::OR:  return Builder.CreateOr(L, R, "ortmp");
    }
    return nullptr;
}

llvm::Value* AssignmentAST::codegen() {
    // 1. Gera o código para o lado direito da atribuição (ex: o número 10)
    llvm::Value* Val = Expr->codegen();
    if (!Val) return nullptr;

    // 2. Procura a variável na tabela de símbolos
    llvm::Value* Variable = NamedValues[Name];
    
    // Se não existe, alocamos espaço para ela na função atual
    if (!Variable) {
        llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
        llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, Name);
        NamedValues[Name] = Alloca;
        Variable = Alloca;
    }

    // Comparações (<, >, =, and, or) produzem valores de 1 bit (i1).
    // Como hoje só temos variáveis de 32 bits, estendemos 0/1 para i32 antes de guardar.
    if (Val->getType()->isIntegerTy(1)) {
        Val = Builder.CreateZExt(Val, llvm::Type::getInt32Ty(TheContext));
    }

    // 3. Armazena o valor na variável (Store)
    Builder.CreateStore(Val, Variable);
    return Val;
}

llvm::Value* WritelnAST::codegen() {
    // 1. Gera o código para o argumento a ser impresso (pode ser string,
    //    número, variável, chamada de função, expressão aritmética, etc.)
    llvm::Value* ArgVal = Arg->codegen();
    if (!ArgVal) return nullptr;

    // 1.5 Comparações (<, >, =, and, or) produzem i1 (1 bit). printf espera
    //     um inteiro de tamanho normal nos argumentos variádicos, então
    //     estendemos 0/1 para i32 antes de imprimir (mesma lógica do AssignmentAST).
    if (ArgVal->getType()->isIntegerTy(1)) {
        ArgVal = Builder.CreateZExt(ArgVal, llvm::Type::getInt32Ty(TheContext));
    }

    // 2. Decide o formato pelo TIPO do valor gerado: ponteiro (i8*/ptr) é
    //    string -> "%s"; qualquer outra coisa nesta linguagem é i32 -> "%d".
    bool IsString = ArgVal->getType()->isPointerTy();
    std::string Fmt = IsString ? "%s" : "%d";
    if (Newline) Fmt += "\n";
    llvm::Value* FmtStr = Builder.CreateGlobalStringPtr(Fmt);

    // 3. Procura (ou declara) a função externa 'printf'
    llvm::Function *PrintfFn = TheModule->getFunction("printf");
    if (!PrintfFn) {
        llvm::FunctionType *PrintfType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(TheContext),
            {llvm::PointerType::getUnqual(TheContext)},
            true // Variadic arguments (...)
        );
        PrintfFn = llvm::Function::Create(PrintfType, llvm::Function::ExternalLinkage, "printf", TheModule.get());
    }

    // 4. Chama printf(formato, valor)
    std::vector<llvm::Value*> ArgsV;
    ArgsV.push_back(FmtStr);
    ArgsV.push_back(ArgVal);
    return Builder.CreateCall(PrintfFn, ArgsV, "printfcall");
}

llvm::Value* BlockAST::codegen() {
    llvm::Value* LastVal = nullptr;
    for (auto &Stmt : Statements) {
        LastVal = Stmt->codegen();
    }
    return LastVal;
}

llvm::Value* IfAST::codegen() {
    llvm::Value* CondV = Cond->codegen();
    if (!CondV) return nullptr;

    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

    // Cria os três blocos: 'then', 'else' e o ponto de junção depois do if
    llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
    llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(TheContext, "else", TheFunction);
    llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(TheContext, "ifcont", TheFunction);

    Builder.CreateCondBr(CondV, ThenBB, ElseBB);

    // Bloco 'then'
    Builder.SetInsertPoint(ThenBB);
    if (Then) Then->codegen();
    Builder.CreateBr(MergeBB);

    // Bloco 'else' (vazio se não houver cláusula else no Mini-Pascal)
    Builder.SetInsertPoint(ElseBB);
    if (Else) Else->codegen();
    Builder.CreateBr(MergeBB);

    // Continuação do código depois do if-then-else
    Builder.SetInsertPoint(MergeBB);
    return nullptr;
}

llvm::Value* WhileAST::codegen() {
    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

    llvm::BasicBlock *CondBB  = llvm::BasicBlock::Create(TheContext, "whilecond", TheFunction);
    llvm::BasicBlock *LoopBB  = llvm::BasicBlock::Create(TheContext, "whilebody", TheFunction);
    llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "afterwhile", TheFunction);

    // Antes de entrar no laço, vai direto checar a condição
    Builder.CreateBr(CondBB);

    // Bloco de condição: avalia a expressão de novo a cada iteração
    Builder.SetInsertPoint(CondBB);
    llvm::Value* CondV = Cond->codegen();
    if (!CondV) return nullptr;
    Builder.CreateCondBr(CondV, LoopBB, AfterBB);

    // Corpo do laço
    Builder.SetInsertPoint(LoopBB);
    if (Body) Body->codegen();
    Builder.CreateBr(CondBB); // volta para reavaliar a condição

    // Continuação do código depois do laço
    Builder.SetInsertPoint(AfterBB);
    return nullptr;
}

llvm::Value* ForAST::codegen() {
    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

    // 1. Avalia a expressão inicial (ex: o "1" em "for i := 1 to 10 do")
    llvm::Value* StartVal = Start->codegen();
    if (!StartVal) return nullptr;

    // 2. Procura (ou cria) a variável de controle do laço na tabela de símbolos
    llvm::Value* Variable = NamedValues[VarName];
    if (!Variable) {
        llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, VarName);
        NamedValues[VarName] = Alloca;
        Variable = Alloca;
    }
    Builder.CreateStore(StartVal, Variable);

    // 3. Avalia a expressão final UMA ÚNICA VEZ, antes de entrar no laço.
    //    Em Pascal, "to <expr>" não é reavaliada a cada iteração.
    llvm::Value* EndVal = End->codegen();
    if (!EndVal) return nullptr;

    llvm::BasicBlock *CondBB  = llvm::BasicBlock::Create(TheContext, "forcond", TheFunction);
    llvm::BasicBlock *LoopBB  = llvm::BasicBlock::Create(TheContext, "forbody", TheFunction);
    llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "afterfor", TheFunction);

    Builder.CreateBr(CondBB);

    // Bloco de condição: continua enquanto var <= EndVal ("to" é um limite inclusivo)
    Builder.SetInsertPoint(CondBB);
    llvm::Value* CurVar = Builder.CreateLoad(llvm::Type::getInt32Ty(TheContext), Variable, VarName.c_str());
    llvm::Value* CondV = Builder.CreateICmpSLE(CurVar, EndVal, "forcmp");
    Builder.CreateCondBr(CondV, LoopBB, AfterBB);

    // Corpo do laço
    Builder.SetInsertPoint(LoopBB);
    if (Body) Body->codegen();

    // Incrementa a variável de controle em 1 e volta para reavaliar a condição
    llvm::Value* CurVar2 = Builder.CreateLoad(llvm::Type::getInt32Ty(TheContext), Variable, VarName.c_str());
    llvm::Value* NextVar = Builder.CreateAdd(
        CurVar2, llvm::ConstantInt::get(TheContext, llvm::APInt(32, 1, true)), "nextvar");
    Builder.CreateStore(NextVar, Variable);
    Builder.CreateBr(CondBB);

    // Continuação do código depois do laço
    Builder.SetInsertPoint(AfterBB);
    return nullptr;
}

llvm::Function* PrototypeAST::codegen() {
    // Se já existe (foi declarado numa primeira passada), reaproveita —
    // permite que uma função chame outra definida mais abaixo no arquivo.
    if (llvm::Function* Existing = TheModule->getFunction(Name)) {
        return Existing;
    }

    // Todos os parâmetros são i32 nesta versão (integer/boolean = i32)
    std::vector<llvm::Type*> ParamTypes(Args.size(), llvm::Type::getInt32Ty(TheContext));
    llvm::Type* RetType = IsFunction ? llvm::Type::getInt32Ty(TheContext)
                                      : llvm::Type::getVoidTy(TheContext);
    llvm::FunctionType* FT = llvm::FunctionType::get(RetType, ParamTypes, false);

    llvm::Function* F = llvm::Function::Create(
        FT, llvm::Function::ExternalLinkage, Name, TheModule.get());

    // Nomeia os parâmetros no IR com os mesmos nomes usados no Mini-Pascal,
    // só para facilitar a leitura do saida.ll
    unsigned Idx = 0;
    for (auto &Arg : F->args()) {
        Arg.setName(Args[Idx++]);
    }
    return F;
}

llvm::Function* FunctionDefAST::codegen() {
    llvm::Function *TheFunction = TheModule->getFunction(Proto->Name);
    if (!TheFunction) TheFunction = Proto->codegen();
    if (!TheFunction) return nullptr;

    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
    Builder.SetInsertPoint(BB);

    // Cada função/procedimento tem seu PRÓPRIO escopo de variáveis: salva a
    // tabela de símbolos de quem chamou (ex: a vazia, antes do main) e
    // começa uma nova só com os parâmetros desta função.
    std::map<std::string, llvm::AllocaInst*> OldNamedValues = NamedValues;
    NamedValues.clear();

    for (auto &Arg : TheFunction->args()) {
        llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, std::string(Arg.getName()));
        Builder.CreateStore(&Arg, Alloca);
        NamedValues[std::string(Arg.getName())] = Alloca;
    }

    // Gera o código do corpo (begin...end)
    Body->codegen();

    if (Proto->IsFunction) {
        // Convenção clássica do Pascal: o valor de retorno é guardado numa
        // "variável" com o mesmo nome da função (ex: "Fatorial := resultado;").
        // Como AssignmentAST já cria essa alocação automaticamente, só
        // precisamos ler de volta o que foi guardado em NamedValues[Nome].
        llvm::Value* RetSlot = NamedValues[Proto->Name];
        llvm::Value* RetVal;
        if (RetSlot) {
            RetVal = Builder.CreateLoad(llvm::Type::getInt32Ty(TheContext), RetSlot, "retval");
        } else {
            std::cerr << "Aviso: função '" << Proto->Name
                      << "' não atribuiu valor de retorno (faltou '" << Proto->Name
                      << " := ...;'); retornando 0." << std::endl;
            RetVal = llvm::ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
        }
        Builder.CreateRet(RetVal);
    } else {
        Builder.CreateRetVoid();
    }

    llvm::verifyFunction(*TheFunction, &llvm::errs());

    // Restaura o escopo de quem chamou
    NamedValues = OldNamedValues;
    return TheFunction;
}