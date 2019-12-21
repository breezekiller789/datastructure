#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=518

int main(int argc, char *argv[]){

    char c;
    while(scanf("%c", &c) != EOF){
        if(c == '\n'){
            continue;
        }
        else
            printf("%d\n", c);

    }

    return 0;
}
