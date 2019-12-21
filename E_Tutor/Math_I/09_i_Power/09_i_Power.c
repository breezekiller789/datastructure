#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=6879

int main(int argc, char *argv[]){
    int i, sum=1;
    while(scanf("%d", &i) != EOF){
        sum = 1;
        if(i>31)
            printf("Value of more than 31\n");
        for(int j=0; j<i; j++){
            sum *= 2;
        }
        printf("%d\n", sum);
    }
    

    return 0;
}
