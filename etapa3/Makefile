#
# UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3
#
# Alunos: Guilherme Schwade e Guilherme Pretto.
#
# Matrículas: 192332 e 213991.
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa3: y.tab.o lex.yy.o main.o hash.o
	gcc -o etapa3 y.tab.o lex.yy.o main.o hash.o
	
main.o: main.c
	gcc -c main.c
	
hash.o: hash.c
	gcc -c hash.c

astree.o: astree.c
	gcc -c astree.c
	
y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.c: parser.y
	yacc -d parser.y -v
	
lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l
	
clean:
	rm *.o y.tab.c y.tab.h lex.yy.c lex.yy.h etapa2
