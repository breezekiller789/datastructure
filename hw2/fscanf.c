#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

int main(int argc, char *argv[]){

    FILE *fp;
    int *origin, *final;
    int Number_Of_Nodes = 0;
    fp = fopen("input1.txt", "r");
    fscanf(fp, "%d", &Number_Of_Nodes);
    origin = (int *)malloc(sizeof(int) * Number_Of_Nodes);
    final = (int *)malloc(sizeof(int) * Number_Of_Nodes);
    printf("%d\n", Number_Of_Nodes);
    for(int idx=0; idx<2; idx++){
        for(int i=0; i<Number_Of_Nodes; i++){
            if(idx == 0){
                fscanf(fp, "%d", origin+i);
                printf("%d ", *(origin+i));
            }
            else{
                fscanf(fp, "%d", final+i);
                printf("%d ", *(final+i));
            }
        }
        printf("\n");
    }
    
    return 0;
}
