#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=2200

int main(int argc, char *argv[]){

    int array[26]={0}, c;

    while((c=getchar()) != EOF){
        //  大寫
        if(c>=65 && c<=90){
            array[c-65]++;
        }
        //  小寫
        else if(c>=97 && c<=122){
            array[c-97]++;
        }
        //  其他的字元不要算
        else
            continue;
    }
    for(int i=0; i<26; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
