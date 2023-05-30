#include "gerar_casos.h"

int* gerarCasoMedio(){
    int* v = malloc(NUM_CASOS * sizeof(int));
    for (int k=0;k<NUM_CASOS;k++){
        int valor = rand() % 1000 + 1;
        v[k] = valor;
    }
    return v;
}

int* gerarPiorCaso1(){
    int* v = malloc(NUM_CASOS * sizeof(int));
    for (int k=0;k<NUM_CASOS;k++){
        v[k] = k;    
    }
    return v;
}

int* gerarPiorCaso2(){
    int* v = malloc(NUM_CASOS * sizeof(int));
    for (int k=NUM_CASOS;k>0;k--){
        v[k] = k;    
    }
    return v;
}

