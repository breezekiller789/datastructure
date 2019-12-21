#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=6882

int main(int argc, char *argv[]){
    float celcius, falh;
    while(scanf("%f", &celcius) != EOF){
        falh = (celcius*9/5) + 32;
        falh = (int)((falh * 100) + 0.5) / 100.0;
        printf("%.1f\n", falh);
    }
    

    return 0;
}
