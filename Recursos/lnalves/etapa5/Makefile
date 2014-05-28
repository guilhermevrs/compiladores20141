## Lucas Neubert Alves - 194917

## Vinícius Garcez Schaurich - 194915

## Compiladores - Etapa5


etapa5: clean y.tab.c lex.yy.c 
	gcc -g -o etapa5 y.tab.c hash.c astree.c semantic.c tacs.c genco.c #lex.yy.c incluido em parser.y

y.tab.c: parser.y
	yacc parser.y -d

lex.yy.c: scanner.l
	lex scanner.l 

etapa5.tgz: clean
	tar cvzf etapa5.tgz .	

clean:
	rm -rf lex.yy.* y.tab.* etapa5 etapa5.tgz
