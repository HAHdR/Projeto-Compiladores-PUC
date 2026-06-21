# Variáveis de compilação
CXX = g++
# llvm-config puxa as flags corretas da LLVM automaticamente
CXXFLAGS = -std=c++14 -Wall `llvm-config --cxxflags`
LLVMLIBS = `llvm-config --libs --system-libs`

# Alvo principal
all: meu_compilador

# Geração do executável acoplando as bibliotecas do LLVM
meu_compilador: src/main.cpp src/codegen.cpp parser.tab.c lex.yy.c
	$(CXX) $(CXXFLAGS) src/main.cpp src/codegen.cpp parser.tab.c lex.yy.c $(LLVMLIBS) -o meu_compilador

parser.tab.c parser.tab.h: src/parser.y
	bison -d src/parser.y

lex.yy.c: src/lexer.l parser.tab.h
	flex src/lexer.l

clean:
	rm -f meu_compilador lex.yy.c parser.tab.c parser.tab.h
