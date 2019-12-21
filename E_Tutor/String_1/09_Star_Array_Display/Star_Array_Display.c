#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1283

int main(int argc, char *argv[]){

    int row, col;

    scanf("%d %d", &col, &row);

    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
