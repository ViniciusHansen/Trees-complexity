#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.c"
//#include "rbtree.c"

#define RANGE 100

int main(){
    // Inserção AVL
    FILE* arq;
    arq = fopen("AVL_insertion.csv", "w");

    if (arq == NULL) {
        printf("Erro ao criar o arquivo.");
        return 1;
    }

    fprintf(arq, "nodes, operations\n");
    for(int i=0;i<RANGE;i++)
        AvlInsertion(i, arq);
    fclose(arq);
    printf("AVL Insertion Experiments done!\n");
    return 0;
}