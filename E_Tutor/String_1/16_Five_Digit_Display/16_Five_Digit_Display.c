#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1339

int rmnewline(char *line){
    char *ptr = line;
    int len=0;
    while(*ptr && *ptr != '\n'){
        ptr++;
        len++;
    }
    *ptr = '\0';
    return len;
}

int main(int argc, char *argv[]){
    int Num, len;
    char line[MaxLine], *ptr;
    //  吃input。
    scanf("%d", &Num);

    //  把整數轉成字串。
    sprintf(line, "%d", Num);

    len = rmnewline(line);
    ptr = line;
    for(int i=0; i<len; i++){
        printf("%c", *ptr);
        if(i != len-1){
            printf("   ");
        }
        else
            printf("\n");
        ptr++;
    }
    

    return 0;
}
