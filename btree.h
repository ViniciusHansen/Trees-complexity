#include <stdlib.h>
#include <stdio.h>

#define NUM_EXP 10

int counter = 0;

typedef struct no_arvore_b {
    int total;
    int* chaves;
    struct no_arvore_b** filhos;
    struct no_arvore_b* pai;
} NoArvoreB;

typedef struct arvoreB {
    NoArvoreB* raiz;
    int ordem;
} ArvoreB;

ArvoreB* criaArvoreB(int);
NoArvoreB* criaNoArvoreB(ArvoreB*);
void percorreArvoreB(NoArvoreB*);
int pesquisaBinariaArvoreB(NoArvoreB*, int);
int localizaChaveArvoreB(ArvoreB*, int);
NoArvoreB* localizaNoArvoreB(ArvoreB*, int);
void adicionaChaveNoArvoreB(NoArvoreB*, NoArvoreB*, int);
int transbordoArvoreB(ArvoreB*, NoArvoreB*);
NoArvoreB* divideNoArvoreB(ArvoreB*, NoArvoreB*);
void adicionaChaveRecursivoArvoreB(ArvoreB*, NoArvoreB*, NoArvoreB*, int);
void adicionaChaveArvoreB(ArvoreB*, int);
