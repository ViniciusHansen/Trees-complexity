#include <stdlib.h>
#include <stdio.h>

#define NUM_EXP 10

int counter = 0;

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    Cor cor;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
    struct no* nulo;
} Arvore;

No* criarNo(Arvore*, No*, int);
void balancear(Arvore*, No*);
void rotacionarEsquerda(Arvore*, No*);
void rotacionarDireita(Arvore*, No*);

Arvore* criar();
int vazia(Arvore*);
No* adicionar(Arvore*, int);
No* localizar(Arvore* arvore, int valor);

void percorrerProfundidadeInOrder(Arvore* arvore, No* no, void (*callback)(int));
void percorrerProfundidadePreOrder(Arvore* arvore, No* no, void (*callback)(int));
void percorrerProfundidadePosOrder(Arvore* arvore, No* no, void (*callback)(int));
void visitar(int valor);

