#include "rbtree.h"
#include "range.h"

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->nulo = NULL;
    arvore->raiz = NULL;

    arvore->nulo = criarNo(arvore, NULL, 0);
    arvore->nulo->cor = Preto;

    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* criarNo(Arvore* arvore, No* pai, int valor) {
    No* no = malloc(sizeof(No));

    no->pai = pai;
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    return no;
}

No* adicionarNo(Arvore* arvore, No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == arvore->nulo) {
            no->direita = criarNo(arvore, no, valor);
            no->direita->cor = Vermelho;

            return no->direita;
        } else {
            return adicionarNo(arvore, no->direita, valor);
        }
    } else {
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNo(arvore, no, valor);
            no->esquerda->cor = Vermelho;

            return no->esquerda;
        } else {
            return adicionarNo(arvore, no->esquerda, valor);
        }
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        arvore->raiz = criarNo(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;
        counter++;

        return arvore->raiz;
    } else {
        No* no = adicionarNo(arvore, arvore->raiz, valor);
        balancear(arvore, no);

        return no;
    }
}

No* localizar(Arvore* arvore, int valor) {
    if (!vazia(arvore)) {
        No* no = arvore->raiz;

        while (no != arvore->nulo) {
            if (no->valor == valor) {
                return no;
            } else {
                no = valor < no->valor ? no->esquerda : no->direita;
            }
        }
    }

    return NULL;
}

void percorrerProfundidadeInOrder(Arvore* arvore, No* no, void (*callback)(int)) {
    if (no != arvore->nulo) {


        percorrerProfundidadeInOrder(arvore, no->esquerda,callback);
        callback(no->valor);
        percorrerProfundidadeInOrder(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePreOrder(Arvore* arvore, No* no, void (*callback)(int)) {
    if (no != arvore->nulo) {
        callback(no->valor);
        percorrerProfundidadePreOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePreOrder(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePosOrder(Arvore* arvore, No* no, void (callback)(int)) {
    if (no != arvore->nulo) {
        percorrerProfundidadePosOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePosOrder(arvore, no->direita,callback);
        callback(no->valor);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

void balancear(Arvore* arvore, No* no) {
    while (no->pai->cor == Vermelho) {
        if (no->pai == no->pai->pai->esquerda) {
            No *tio = no->pai->pai->direita;

            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto;

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->direita) {
                    no = no->pai; //Caso 2
                    rotacionarEsquerda(arvore, no); //Caso 2
                    counter++;
                } else {
                    no->pai->cor = Preto;
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarDireita(arvore, no->pai->pai); //Caso 3
                    counter++;
                }
            }
        } else {
            No *tio = no->pai->pai->esquerda;

            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto;

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai; //Caso 2
                    rotacionarDireita(arvore, no); //Caso 2
                    counter++;
                } else {
                    no->pai->cor = Preto;
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarEsquerda(arvore, no->pai->pai); //Caso 3
                    counter++;
                }
            }
        }
    }
    arvore->raiz->cor = Preto; //Conserta possível quebra regra 2
}

void rotacionarEsquerda(Arvore* arvore, No* no) {
    No* direita = no->direita;
    no->direita = direita->esquerda;

    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;

    if (no->pai == arvore->nulo) {
        arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = direita;
    } else {
        no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;
}

void rotacionarDireita(Arvore* arvore, No* no) {
    No* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;

    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }

    esquerda->pai = no->pai;

    if (no->pai == arvore->nulo) {
        arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = esquerda;
    } else {
        no->pai->direita = esquerda;
    }

    esquerda->direita = no;
    no->pai = esquerda;
}


int* gerarCasoMedio(int numero_casos){
    int* v = malloc(numero_casos * sizeof(int));
    for (int k=0;k<numero_casos;k++){
        int valor = rand() % 1000 + 1;
        v[k] = valor;
    }
    return v;
}

void RBInsertion(int numero_casos, FILE* arq){
    
    double tempo_execucao;
    Arvore* a = criar();
    int operacoes[NUM_EXP];
    
    //caso medio
    for(int i=0;i<NUM_EXP;i++){
        int* v = malloc(numero_casos * sizeof(int));
        v = gerarCasoMedio(numero_casos);
        for(int j=0;j<numero_casos;j++){
            adicionar(a,v[j]);
        }
        free(v);
        operacoes[i] = counter;
        counter = 0;
    }

    int media_operacoes = 0;
    for (int i =0;i<NUM_EXP;i++){
        media_operacoes += operacoes[i];
    }
    media_operacoes /= NUM_EXP;
    
    fprintf(arq, "%i, %i\n", numero_casos, media_operacoes);
    return;
}