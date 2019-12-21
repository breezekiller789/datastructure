#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

int rmnewline(char *line){
    char *ptr = line;
    int len=0;
    while(*ptr && *ptr != '\n'){
        len++;
        ptr++;
    }
    *ptr = '\0';
    return len;
}

int main(int argc, char *argv[]){

    char line[MaxLine];
    int Num_Line=1, len, i=0;
    while(fgets(line, MaxLine, stdin) != NULL){
        if(i==0){
            i++;
            continue;
        }
        len = rmnewline(line);
        for(int j=len-1; j>=0; j--){
            printf("%c", line[j]);
        }
        printf("\n");
    }

    return 0;
}
