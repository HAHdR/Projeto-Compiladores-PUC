#ifndef AST_H
#define AST_H

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
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

// Operadores binários suportados: aritméticos, relacionais e lógicos
enum class BinOp { ADD, SUB, MUL, DIV, LT, GT, EQ, AND, OR };

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

// Classe para o comando writeln
class WritelnAST : public ASTNode {
    std::unique_ptr<ASTNode> Arg;
public:
    WritelnAST(std::unique_ptr<ASTNode> Arg) : Arg(std::move(Arg)) {}
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

// Bloco principal que contém uma lista de comandos (o begin ... end)
class BlockAST : public ASTNode {
    std::vector<std::unique_ptr<ASTNode>> Statements;
public:
    void addStatement(std::unique_ptr<ASTNode> stmt) {
        Statements.push_back(std::move(stmt));
    }
    llvm::Value* codegen() override;
};

#endif