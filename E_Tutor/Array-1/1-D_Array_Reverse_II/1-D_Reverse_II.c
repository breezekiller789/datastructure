#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1289

void rmnewline(char *line){
    char *ptr = line;
    while(*ptr && *ptr != '\n')
        ptr++;
    *ptr = '\0';
}

int main(int argc, char *argv[]){

    int array[100], i, cnt=0, Num=0;
    char *line, *ptr;
    line = (char *)malloc(sizeof(char) * MaxLine);

    while(fgets(line, MaxLine, stdin) != NULL){
        rmnewline(line);
        ptr = line;
        cnt = 0;
        /* printf("Before Reverse\n"); */
        while(1){
            Num = atoi(ptr);
            array[cnt++] = Num;
            /* printf("%d ", Num); */
            while(isdigit(*ptr)){
                ptr++;
            }
            while(isspace(*ptr)){
                ptr++;
            }
            if(*ptr == '\0')
                break;
        }
        /* printf("\n"); */
        /* printf("After Reverse\n"); */
        for(int i=cnt-1; i>=0; i--){
            printf("%d ", array[i]);
        }
        printf("\n");
    }


    return 0;
}
