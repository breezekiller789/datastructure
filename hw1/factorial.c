#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

int fac(int c){
    if(c == 1)
        return 1;
    if(c > 1)
        return fac(c-1) * c;
}

int main(int argc, char *argv[]){

    int c;
    scanf("%d", &c);
    printf("%d\n", fac(c));

    return 0;
}
