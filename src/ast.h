#ifndef AST_H
#define AST_H

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Function.h>
#include <string>
#include <vector>
#include <memory>
#include <map> // <- ADICIONE ESTA LINHA

// Variáveis globais do LLVM (geralmente definidas no main ou codegen.cpp)
extern llvm::LLVMContext TheContext;
extern llvm::IRBuilder<> Builder;
extern std::unique_ptr<llvm::Module> TheModule;
extern std::map<std::string, llvm::AllocaInst*> NamedValues; // Tabela de símbolos local

// Classe base para todos os nós da AST
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual llvm::Value* codegen() = 0;
};

// Classe para expressões numéricas (ex: 10)
class NumberAST : public ASTNode {
    int Val;
public:
    NumberAST(int Val) : Val(Val) {}
    llvm::Value* codegen() override;
};

// Classe para strings (ex: "Ola Mundo")
class StringAST : public ASTNode {
    std::string Str;
public:
    StringAST(const std::string &Str) : Str(Str) {}
    llvm::Value* codegen() override;
};

// Classe para ler o valor atual de uma variável (ex: usar 'x' dentro de uma expressão)
class VariableAST : public ASTNode {
    std::string Name;
public:
    VariableAST(const std::string &Name) : Name(Name) {}
    llvm::Value* codegen() override;
};

// Classe para chamada de função/procedimento (ex: Fatorial(5), EhPrimo(n))
// Serve tanto como expressão (função, usa o retorno) quanto como statement
// (procedimento, o retorno é descartado pelo BlockAST).
class CallExprAST : public ASTNode {
    std::string Callee;
    std::vector<std::unique_ptr<ASTNode>> Args;
public:
    CallExprAST(const std::string &Callee, std::vector<std::unique_ptr<ASTNode>> Args)
        : Callee(Callee), Args(std::move(Args)) {}
    llvm::Value* codegen() override;
};

// Operadores binários suportados: aritméticos, relacionais e lógicos
enum class BinOp { ADD, SUB, MUL, DIV, MOD, LT, GT, EQ, AND, OR };

// Classe para expressões binárias (ex: a + b, x < 3, p and q)
class BinaryExprAST : public ASTNode {
    BinOp Op;
    std::unique_ptr<ASTNode> LHS, RHS;
public:
    BinaryExprAST(BinOp Op, std::unique_ptr<ASTNode> LHS, std::unique_ptr<ASTNode> RHS)
        : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    llvm::Value* codegen() override;
};

// Classe para atribuição de variáveis (ex: x := 10)
class AssignmentAST : public ASTNode {
    std::string Name;
    std::unique_ptr<ASTNode> Expr;
public:
    AssignmentAST(const std::string &Name, std::unique_ptr<ASTNode> Expr)
        : Name(Name), Expr(std::move(Expr)) {}
    llvm::Value* codegen() override;
};

// Classe para os comandos write/writeln. Aceita QUALQUER expressão (string,
// inteiro, resultado de função, etc.) — o codegen decide em tempo de geração
// se imprime como "%s" ou "%d" observando o tipo LLVM do valor produzido.
// Newline=true -> writeln (quebra de linha no final); false -> write (sem quebra).
class WritelnAST : public ASTNode {
    std::unique_ptr<ASTNode> Arg;
    bool Newline;
public:
    WritelnAST(std::unique_ptr<ASTNode> Arg, bool Newline = true)
        : Arg(std::move(Arg)), Newline(Newline) {}
    llvm::Value* codegen() override;
};

// Classe para if-then ou if-then-else (Else é nullptr quando não há 'else')
class IfAST : public ASTNode {
    std::unique_ptr<ASTNode> Cond;
    std::unique_ptr<ASTNode> Then;
    std::unique_ptr<ASTNode> Else;
public:
    IfAST(std::unique_ptr<ASTNode> Cond, std::unique_ptr<ASTNode> Then, std::unique_ptr<ASTNode> Else)
        : Cond(std::move(Cond)), Then(std::move(Then)), Else(std::move(Else)) {}
    llvm::Value* codegen() override;
};

// Classe para o laço while...do
class WhileAST : public ASTNode {
    std::unique_ptr<ASTNode> Cond;
    std::unique_ptr<ASTNode> Body;
public:
    WhileAST(std::unique_ptr<ASTNode> Cond, std::unique_ptr<ASTNode> Body)
        : Cond(std::move(Cond)), Body(std::move(Body)) {}
    llvm::Value* codegen() override;
};

// Classe para o laço for VarName := Start to End do Body
// (estilo Pascal: limite inclusivo, passo fixo de +1, sem "downto")
class ForAST : public ASTNode {
    std::string VarName;
    std::unique_ptr<ASTNode> Start;
    std::unique_ptr<ASTNode> End;
    std::unique_ptr<ASTNode> Body;
public:
    ForAST(const std::string &VarName, std::unique_ptr<ASTNode> Start,
           std::unique_ptr<ASTNode> End, std::unique_ptr<ASTNode> Body)
        : VarName(VarName), Start(std::move(Start)), End(std::move(End)), Body(std::move(Body)) {}
    llvm::Value* codegen() override;
};

// Bloco principal que contém uma lista de comandos (o begin ... end)
class BlockAST : public ASTNode {
    std::vector<std::unique_ptr<ASTNode>> Statements;
public:
    void addStatement(std::unique_ptr<ASTNode> stmt) {
        Statements.push_back(std::move(stmt));
    }
    llvm::Value* codegen() override;
};

// Assinatura de uma função/procedimento: nome, nomes dos parâmetros (todos
// tratados como integer/boolean = i32 nesta versão) e se é função (retorna
// valor) ou procedimento (não retorna).
class PrototypeAST {
public:
    std::string Name;
    std::vector<std::string> Args;
    bool IsFunction;
    PrototypeAST(const std::string &Name, std::vector<std::string> Args, bool IsFunction)
        : Name(Name), Args(std::move(Args)), IsFunction(IsFunction) {}
    llvm::Function* codegen();
};

// Definição completa: protótipo + corpo (begin...end). Não herda de ASTNode
// porque seu codegen() produz uma llvm::Function*, não um llvm::Value*.
class FunctionDefAST {
public:
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<BlockAST> Body;
    FunctionDefAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<BlockAST> Body)
        : Proto(std::move(Proto)), Body(std::move(Body)) {}
    llvm::Function* codegen();
};

// Lista global de todas as funções/procedimentos declarados no programa,
// preenchida pelo parser.y e consumida pelo main.cpp antes de gerar o main().
extern std::vector<std::unique_ptr<FunctionDefAST>> FunctionDecls;

#endif