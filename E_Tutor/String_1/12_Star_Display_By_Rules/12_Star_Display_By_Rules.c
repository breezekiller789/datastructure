#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1320

int main(int argc, char *argv[]){

    int row, col;
    scanf("%d %d", &row, &col);
    
    //  處理row比col大的情況，要反過來，做完直接離開。
    if(row > col){
        for(int i=row; i>=col; i--){
            for(int j=0; j<i; j++){
                printf("*");
            }
            printf("\n");
        }
        exit(1);
    }

    //  row比col小，那就簡單。
    for(int i=row; i<=col; i++){
        for(int j=0; j<i; j++){
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
