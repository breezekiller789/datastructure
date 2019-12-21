#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024


//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1285

int main(int argc, char *argv[]){
    int c;
    scanf("%d", &c);

    for(int i=1; i<=c; i++){
        for(int j=0; j<c-i; j++){
            printf(" ");
        }
        for(int j=0; j<i; j++){
            printf("*");
        }
        printf("\n");
    }
    

    return 0;
}
