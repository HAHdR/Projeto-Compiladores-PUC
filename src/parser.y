%{
#include <iostream>
#include <string>
#include <vector>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

extern int yylex();
void yyerror(const char *s);
extern int line_number;

// Linkagem direta com os ponteiros instanciados no main.cpp
extern llvm::LLVMContext* TheContext;
extern llvm::Module* TheModule;
extern llvm::IRBuilder<>* Builder;

llvm::Function* getPrintfPrototype() {
    llvm::Function* printfFunc = TheModule->getFunction("printf");
    if (!printfFunc) {
        llvm::FunctionType* printfType = llvm::FunctionType::get(
            llvm::IntegerType::getInt32Ty(*TheContext),
            llvm::PointerType::get(llvm::IntegerType::getInt8Ty(*TheContext), 0),
            true
        );
        printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", TheModule);
    }
    return printfFunc;
}
%}

%union {
    int num;
    std::string* str;
}

%token TOK_PROGRAM TOK_VAR TOK_BEGIN TOK_END
%token TOK_INTEGER TOK_BOOLEAN TOK_ASSIGN
%token TOK_IF TOK_THEN TOK_ELSE TOK_WHILE TOK_DO TOK_FOR TOK_TO
%token TOK_PROCEDURE TOK_FUNCTION TOK_WRITE TOK_WRITELN
%token TOK_AND TOK_OR TOK_NOT TOK_EQ TOK_LT TOK_GT
%token <str> TOK_IDENTIFIER TOK_STRING
%token <num> TOK_NUM

%left '+' '-'

%%

program:
    TOK_PROGRAM TOK_IDENTIFIER ';' 
    {
        // Cria o ponto de entrada seguro 'main' usando os ponteiros validados
        llvm::FunctionType* mainType = llvm::FunctionType::get(llvm::IntegerType::getInt32Ty(*TheContext), false);
        llvm::Function* mainFunc = llvm::Function::Create(mainType, llvm::Function::ExternalLinkage, "main", TheModule);
        llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*TheContext, "entry", mainFunc);
        Builder->SetInsertPoint(entryBlock);
    }
    declarations block '.' 
    { 
        Builder->CreateRet(llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(*TheContext), 0));
        std::cout << "Analise Sintatica e geracao de AST concluidas!\n"; 
    }
    ;

declarations:
    TOK_VAR variable_list
    | 
    ;

variable_list:
    variable_list variable_declaration
    | variable_declaration
    ;

variable_declaration:
    TOK_IDENTIFIER ':' type ';'
    ;

type:
    TOK_INTEGER
    | TOK_BOOLEAN
    | TOK_STRING
    ;

block:
    TOK_BEGIN statements TOK_END
    ;

statements:
    statements statement ';'
    | statement ';'
    | 
    ;

statement:
    TOK_IDENTIFIER TOK_ASSIGN expression
    | TOK_WRITELN '(' TOK_STRING ')'
    {
        // Se o ponteiro da string existir, faz o tratamento correto
        std::string cleanStr = "";
        if ($3) {
            cleanStr = *$3;
            if(cleanStr.front() == '"' && cleanStr.back() == '"') {
                cleanStr = cleanStr.substr(1, cleanStr.length() - 2);
            }
        }
        cleanStr += "\n";

        llvm::Value* strGlobal = Builder->CreateGlobalStringPtr(cleanStr);
        std::vector<llvm::Value*> printfArgs;
        printfArgs.push_back(strGlobal);
        Builder->CreateCall(getPrintfPrototype(), printfArgs);
    }
    | TOK_WRITELN '(' expression ')'
    | block
    ;

expression:
    TOK_NUM
    | TOK_IDENTIFIER
    | expression '+' expression
    | expression '-' expression
    ;

%%

void yyerror(const char *s) {
    std::cerr << "Erro Sintatico na linha " << line_number << ": " << s << "\n";
}
