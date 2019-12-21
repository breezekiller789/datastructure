#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

int rmnewline(char *line){
    char *ptr = line;
    int len=0;
    while(*ptr && *ptr !='\n'){
        ptr++;
        len++;
    }
    *ptr = '\0';
    return len;
}

int main(int argc, char *argv[]){

    char line[MaxLine], *ptr;
    int len=0,i;
    while(fgets(line, MaxLine, stdin) != NULL){
        len = rmnewline(line);
        ptr = line;
        for(i=0; i<(len/2); i++){
            if(ptr[i] != ptr[len-1-i]){
                break;
            }
        }
        if(i == (len/2)){
            printf("YES\n");
        }
        else
            printf("NO\n");
    }
    

    return 0;
}
