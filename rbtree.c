#include "rbtree.h"

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
        //counter++;

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


int main(){
    clock_t inicio, fim;
    double tempo_execucao;
    Arvore* a = criar();
    double medio_tempos[NUM_EXP];
    int medio_operacoes[NUM_EXP];
    double pior_tempos[NUM_EXP];
    int pior_operacoes[NUM_EXP];
    //caso medio
    for(int i=0;i<NUM_EXP;i++){
        inicio = clock(); // Marca o início da contagem de tempo
        int* v = malloc(NUM_CASOS * sizeof(int));
        v = gerarCasoMedio();
        for(int j=0;j<NUM_CASOS;j++){
            adicionar(a,v[j]);
        }
        free(v);
        fim = clock(); // Marca o final da contagem de tempo
        medio_operacoes[i] = counter;
        medio_tempos[i] = (double)(fim - inicio) / CLOCKS_PER_SEC;
        counter = 0;
    }
    //pior caso
    for(int i=0;i<NUM_EXP;i++){
        inicio = clock(); // Marca o início da contagem de tempo
        int* v = malloc(NUM_CASOS * sizeof(int));
        if (i % 2 == 0) v= gerarPiorCaso1();
        else v=gerarPiorCaso2();
        for(int j=0;j<NUM_CASOS;j++){
            adicionar(a,v[j]);
        }
        free(v);
        fim = clock(); // Marca o final da contagem de tempo
        pior_operacoes[i] = counter;
        pior_tempos[i] = (double)(fim - inicio) / CLOCKS_PER_SEC;
        counter = 0;
    }

    int medio_media_operacoes = 0;
    for (int i =0;i<NUM_EXP;i++){
        medio_media_operacoes += medio_operacoes[i];
    }
    medio_media_operacoes /= NUM_EXP;
    
    double medio_media_tempo =0;
    for (int i =0;i<NUM_EXP;i++){
        medio_media_tempo += medio_tempos[i];
    }
    medio_media_tempo /= NUM_EXP;

    int pior_media_operacoes = 0;
    for (int i =0;i<NUM_EXP;i++){
        pior_media_operacoes += pior_operacoes[i];
    }
    pior_media_operacoes /= NUM_EXP;

    double pior_media_tempo = 0;
    for (int i =0;i<NUM_EXP;i++){
        pior_media_tempo += pior_tempos[i];
    }
    pior_media_tempo /= NUM_EXP;

    printf("\nArvore RB, %i casos, %i experimentos:\n", NUM_CASOS,NUM_EXP);
    printf("Caso Médio:\n");
    printf("Media Tempo de execução: %lf segundos\nem média %i operações\n", medio_media_tempo, medio_media_operacoes);
    printf("Pior Caso:\n");
    printf("Media Tempo de execução: %lf segundos\nem média %i operações\n\n", pior_media_tempo, pior_media_operacoes);
    return 0;
}
/*
int main() {
    Arvore* a = criar();

    adicionar(a,7);
    adicionar(a,6);
    adicionar(a,5);
    adicionar(a,4);
    adicionar(a,3);
    adicionar(a,2);
    adicionar(a,1);

    printf("In-order: ");
    percorrerProfundidadeInOrder(a, a->raiz,visitar);
    printf("\n");
}
*/