#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

void display(int *array){
    for(int i=0; i<10; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void reverse(int *array){
    for(int i=0; i<5; i++){
        int tmp = array[i];
        array[i] = array[9-i];
        array[9-i] = tmp;
    }
}

int main(int argc, char *argv[]){
    
    int array[10] = {0}, i=0;
    while(scanf("%d", &array[i]) != EOF){
        i++;
    }
    /* display(array); */
    reverse(array);
    display(array);
    

    return 0;
}
