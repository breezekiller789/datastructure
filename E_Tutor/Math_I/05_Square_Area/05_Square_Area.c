#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=6867

int main(int argc, char *argv[]){



    float a;
    while(scanf("%f", &a) != EOF){
        a = a*a;
        float b =(int)((a * 100) + 0.5) / 100.0;
        printf("%.1f\n", b);
    }
    

    return 0;
}
