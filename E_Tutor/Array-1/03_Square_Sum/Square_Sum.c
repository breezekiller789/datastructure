#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1291

void rmnewline(char *line){
    char *ptr = line;
    while(*ptr && *ptr != '\n')
        ptr++;
    *ptr = '\0';
}

int main(int argc, char *argv[]){

    int i;
    long long Sum=0, Num=0;
    char *line, *ptr;
    line = (char *)malloc(sizeof(char) * MaxLine);

    while(fgets(line, MaxLine, stdin) != NULL){
        rmnewline(line);
        ptr = line;
        /* printf("Before Reverse\n"); */
        Sum=0;
        while(1){
            Num = atoi(ptr);
            Sum += (Num*Num*Num);
            while(isdigit(*ptr)){
                ptr++;
            }
            while(isspace(*ptr)){
                ptr++;
            }
            if(*ptr == '\0')
                break;
        }
        printf("%lld\n", Sum);
    }


    return 0;
}
