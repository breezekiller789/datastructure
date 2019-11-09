#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

int main(int argc, char *argv[]){

    int **a, **b;
    a = (int **)malloc(sizeof(int *) * 5);
    for(int i=0; i<5; i++){
        *(a+i) = (int *)malloc(sizeof(int) * 5);
        for(int j=0; j<5; j++){
            (*(a+i))[j] = j;
            /* printf("%d ", (*(a+i))[j]); */
        }
        /* printf("\n"); */
    }
    b = (int **)malloc(sizeof(int *) * 5);
    for(int i=0; i<5; i++){
        *(b+i) = (int *)malloc(sizeof(int)*5);
        memcpy(*(b+i), *(a+i), sizeof(int) * 5);
        for(int j=0; j<5; j++){
            (*(a+i))[j] = j;
            printf("%d ", (*(a+i))[j]);
        }
        printf("\n");
    }
    int c = memcmp((*a)[0], (*b)[0], sizeof(int) * 5);
    printf("%d\n", c);

    /* *(a+3) = 0; */
    /* for(int i=0; i<7; i++){ */
    /*     if(*(a+i) == NULL) */
    /*         continue; */
    /*     for(int j=0; j<5; j++){ */
    /*         printf("%d ", (*(a+i))[j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */

    return 0;
}
