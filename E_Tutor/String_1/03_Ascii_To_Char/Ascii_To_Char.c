#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=512

int main(int argc, char *argv[]){

    int c;
    while(scanf("%d", &c) != EOF){
        printf("%c\n", c);
    }

    return 0;
}
