#include "ast.h"
#include <iostream>

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
    // Cria uma string global no módulo LLVM
    return Builder.CreateGlobalStringPtr(Str + "\n");
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
    // 1. Gera o código para o argumento a ser impresso
    llvm::Value* ArgVal = Arg->codegen();
    if (!ArgVal) return nullptr;

    // 2. Procura a função externa 'printf' no módulo
    llvm::Function *PrintfFn = TheModule->getFunction("printf");
    if (!PrintfFn) {
        // Se não existir, declara a assinatura: int printf(ptr, ...)
        llvm::FunctionType *PrintfType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(TheContext),
            {llvm::PointerType::getUnqual(TheContext)},
            true // Variadic arguments (...)
        );
        PrintfFn = llvm::Function::Create(PrintfType, llvm::Function::ExternalLinkage, "printf", TheModule.get());
    }

    // 3. Chama a função printf passando o argumento
    std::vector<llvm::Value*> ArgsV;
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