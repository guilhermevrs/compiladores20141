#
# UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 5
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

etapa5: y.tab.o lex.yy.o hash.o astree.o main.o genco.o tacs.o
	gcc -o etapa5 y.tab.o lex.yy.o hash.o astree.o main.o genco.o tacs.o

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
	yacc parser.y -d -v

lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l

genco.o: genco.c
	gcc -c genco.c

tacs.o: tacs.c
	gcc -c tacs.c

clean:
	rm *.o y.tab.c y.tab.h lex.yy.c lex.yy.h etapa5
