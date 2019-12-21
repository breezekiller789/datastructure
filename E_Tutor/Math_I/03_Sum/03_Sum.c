#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=6861

int main(int argc, char *argv[]){

    int a, b;
    while(scanf("%d %d", &a, &b) != EOF){
        printf("%d\n", a+b);
    }

    return 0;
}
