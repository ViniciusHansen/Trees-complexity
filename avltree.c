#include "avltree.h"

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;

    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* adicionarNo(No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            //printf("Adicionando %d\n",valor);
            No* novo = malloc(sizeof(No));
            novo->valor = valor;
            novo->pai = no;
            novo->esquerda = NULL;
            novo->direita = NULL;

            no->direita = novo;

            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            //printf("Adicionando %d\n",valor);
            No* novo = malloc(sizeof(No));
			novo->valor = valor;
            novo->pai = no;
            novo->esquerda = NULL;
            novo->direita = NULL;

            no->esquerda = novo;

            return novo;
        } else {
            return adicionarNo(no->esquerda, valor);
        }
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        //printf("Adicionando %d\n",valor);
        No* novo = malloc(sizeof(No));
        novo->valor = valor;
        novo->pai = NULL;
        novo->esquerda = NULL;
        novo->direita = NULL;

        arvore->raiz = novo;

        //counter++;
        return novo;
    } else {
        No* no = adicionarNo(arvore->raiz, valor);
        balanceamento(arvore, no);
        return no;
    }
}

No* localizar(No* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizar(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizar(no->direita, valor);
            }
        }
    }

    return NULL;
}

void percorrer(No* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrer(no->esquerda,callback);
        callback(no->valor);
        percorrer(no->direita,callback);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

void balanceamento(Arvore* arvore, No* no) {
    while (no != NULL) {
        int fator = fb(no);

        if (fator > 1) { //árvore mais pesada para esquerda
            //rotação para a direita
            if (fb(no->esquerda) > 0) {
                //printf("RSD(%d)\n",no->valor);
                rsd(arvore, no); //rotação simples a direita, pois o FB do filho tem sinal igual
                counter++;
            } else {
                //printf("RDD(%d)\n",no->valor);
                rdd(arvore, no); //rotação dupla a direita, pois o FB do filho tem sinal diferente
                counter++;
            }
        } else if (fator < -1) { //árvore mais pesada para a direita
            //rotação para a esquerda
            if (fb(no->direita) < 0) {
                //printf("RSE(%d)\n",no->valor);
                rse(arvore, no); //rotação simples a esquerda, pois o FB do filho tem sinal igual
                counter++;
            } else {
                //printf("RDE(%d)\n",no->valor);
                rde(arvore, no); //rotação dupla a esquerda, pois o FB do filho tem sinal diferente
                counter++;
            }
        }

        no = no->pai;
    }
}

int altura(No* no){
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }

    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

int fb(No* no) {
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }

    return esquerda - direita;
}

No* rse(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    }

    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}



No* rsd(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    }

    no->esquerda = esquerda->direita;
    no->pai = esquerda;

    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

No* rde(Arvore* arvore, No* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

No* rdd(Arvore* arvore, No* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
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

    printf("\nArvore AVL, %i casos, %i experimentos:\n", NUM_CASOS,NUM_EXP);
    printf("Caso Médio:\n");
    printf("Media Tempo de execução: %lf segundos\nem média %i operações\n", medio_media_tempo, medio_media_operacoes);
    printf("Pior Caso:\n");
    printf("Media Tempo de execução: %lf segundos\nem média %i operações\n\n", pior_media_tempo, pior_media_operacoes);
    return 0;
}

        //printf("In-order: ");
        //percorrer(a->raiz,visitar);
        //printf("\n");