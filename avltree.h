#include <stdlib.h>
#include <stdio.h>

int counter = 0;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

void balanceamento(Arvore*, No*);
int altura(No*);
int fb(No*);
No* rsd(Arvore*, No*);
No* rse(Arvore*, No*);
No* rdd(Arvore*, No*);
No* rde(Arvore*, No*);
int* RBgerarCasoMedio(int numero_casos);
Arvore* criar();
int RBvazia(Arvore* arvore);
No* adicionarNo(No* no, int valor);
No* RBadicionar(Arvore* arvore, int valor);
No* localizar(No* no, int valor);
void percorrer(No* no, void (*callback)(int));
void RBvisitar(int valor);

