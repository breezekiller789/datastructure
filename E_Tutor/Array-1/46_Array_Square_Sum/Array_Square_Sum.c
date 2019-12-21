#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=3071

int main(int argc, char *argv[]){

    float array[20] = {0}, sum=0, accumulate;
    int i=0;
    while(scanf("%f", &accumulate) != EOF){
        sum += (accumulate*accumulate);
        i++;
    }
    //  檢查算出來的總和對不對。
    /* printf("%.10f\n", sum); */

    //  做四捨五入
    float b =(int)((sum * 1000000) + 0.5) / 1000000.0;
    printf("%.6f\n", sum);

    return 0;
}
