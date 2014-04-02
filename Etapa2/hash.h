/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 2

Alunos: Guilherme Schwade e Guilherme Pretto

Matrícula: 192332 e 213991.
*/

#define HASH_SIZE 997

typedef struct nome_interno{
    char *text;
    int type;
    int intVal;
    char charVal;
    int boolVal;
    struct nome_interno *next;
}HASH_NODE;

void hash_init(void);
int hash_address(char *text);
HASH_NODE *hash_find(char *text);
HASH_NODE *hash_insert(char *text, int type);
void hash_print(void);
