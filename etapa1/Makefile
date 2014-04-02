#
# UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 1
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

etapa1: hash.o
	gcc -o etapa1 lex.yy.o hash.o

hash.o: lex.yy.o
	gcc -c hash.c

lex.yy.o: lex.yy.c hash.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	flex scanner.l

clean:
	rm lex.yy.c etapa1
