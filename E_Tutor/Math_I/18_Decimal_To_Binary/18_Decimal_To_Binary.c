#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=6906

int main(int argc, char *argv[]){
    int num, array[8]={0}, carry;
    while(scanf("%d", &num) != EOF){
        if(num > 0){
            for(int i=7; i>=0; i--){
                array[i] = num%2;
                num = num/2;
            }
        }
        else{
            num = abs(num);
            for(int i=7; i>=0; i--){
                //  2's complement反過來
                if(num%2 == 1){
                    array[i] = 0;
                }
                else{
                    array[i] = 1;
                }
                num = num/2;
            }
            //  可能會有carry
            array[7] += 1;
            for(int i=7; i>=0; i--){
                if(array[i]>1){
                    array[i] = 0;
                    array[i-1] += 1;
                }
            }

        }
        for(int i=0; i<8; i++){
            printf("%d", array[i]);
        }
        printf("\n");
    }
    

    return 0;
}
