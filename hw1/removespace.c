#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#define MaxLine 1024

void rmnewline(char *line){
    char *ptr = line;
    while(*ptr && *ptr != '\n')
        ptr++;
    *ptr = '\0';
}

int main(int argc, char *argv[]){

    char line[MaxLine], *ptr, *qtr, *words[MaxLine];
    int i=0, cnt=0;
    while(fgets(line, MaxLine, stdin) != NULL){
        rmnewline(line);
        ptr = line;
        cnt=0;
        while(1){
            while(isspace(*ptr)){
                ptr++;
            }
            words[cnt] = (char *)malloc(sizeof(char) * strlen(line) + 1);
            qtr = words[cnt];
            cnt++;
            while(*ptr && !isspace(*ptr)){
                *qtr = *ptr;
                ptr++;
                qtr++;
            }
            *qtr = '\0';
            if(isspace(*ptr)){
                while(isspace(*ptr)){
                    ptr++;
                }
                if(*ptr == '\0')
                    break;
                else
                    continue;
            }
            else
                break;
        }
        for(i=0; i<cnt; i++){
            printf("%s", words[i]);
            if(i != cnt-1){
                printf(" ");
            }
            else
                printf("\n");
        }
    }
    /* printf("%d\n", cnt); */

    return 0;
}
