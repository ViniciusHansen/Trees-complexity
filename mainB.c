#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.c"
#include "range.h"


int main(){

    FILE* arq = fopen("data/B1_insertion.csv", "w");

    if (arq == NULL) {
        printf("Erro ao criar o arquivo.");
        return 1;
    }

    fprintf(arq, "nodes, operations\n");
    for(int i=0;i<RANGE;i++)
        BInsertion(i, arq, 1);

    fclose(arq);
    printf("all B1 Insertion Experiments done!\n");



    FILE* arq2 = fopen("data/B5_insertion.csv", "w");

    if (arq2 == NULL) {
        printf("Erro ao criar o arquivo.");
        return 1;
    }

    fprintf(arq2, "nodes, operations\n");
    for(int i=0;i<RANGE;i++)
        BInsertion(i, arq2, 5);

    fclose(arq2);
    printf("all B5 Insertion Experiments done!\n");


    FILE* arq3 = fopen("data/B10_insertion.csv", "w");

    if (arq3 == NULL) {
        printf("Erro ao criar o arquivo.");
        return 1;
    }

    fprintf(arq3, "nodes, operations\n");
    for(int i=0;i<RANGE;i++)
        BInsertion(i, arq3, 5);

    fclose(arq3);
    printf("all B10 Insertion Experiments done!\n");


    return 0;
}
