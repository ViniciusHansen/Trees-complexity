#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.c"

#define RANGE 100

int main(){
    
    FILE* arq = fopen("data/RB_insertion.csv", "w");

    if (arq == NULL) {
        printf("Erro ao criar o arquivo.");
        return 1;
    }

    fprintf(arq, "nodes, operations\n");
    for(int i=0;i<RANGE;i++)
        RBInsertion(i, arq);
    fclose(arq);
    printf("all RB Insertion Experiments done!\n");
    return 0;
}