#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1690

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

void reverse(char *line, int len){
    char *ptr = line;
    for(int i=0; i<len/2; i++){
        char tmp = ptr[i];
        ptr[i] = ptr[len-1-i];
        ptr[len-1-i] = tmp;
    }
}

int main(int argc, char *argv[]){

    char line[MaxLine], *ptr;
    int len;
    while(fgets(line, MaxLine, stdin) != NULL){
        len = rmnewline(line);
        reverse(line, len);
        ptr = line;
        for(int i=0; i<len; i++){
            if(isalpha(ptr[i])){
                //  Capital
                if(ptr[i]<=90 && ptr[i]>=65){
                    ptr[i] = tolower(ptr[i]);
                }
                else
                    ptr[i] = toupper(ptr[i]);
            }
            else
                continue;
        }
        printf("%s\n", line);
    }

    return 0;
}
