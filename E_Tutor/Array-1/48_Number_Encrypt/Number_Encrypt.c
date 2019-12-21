#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=3075

void rmnewline(char *line){
    char *ptr = line;
    while(*ptr && *ptr != '\n')
        ptr++;
    *ptr = '\0';
}

int main(int argc, char *argv[]){

    char line[10], *ptr, output[4];
    int array[4];
    fgets(line, 10, stdin);
    rmnewline(line);
    ptr = line;
    for(int i=0; i<4; i++){
        output[i] = '0' + (*(ptr+i)-48+7)%10;
        /* printf("%c\n", output[i]); */
        /* printf("%d\n", *(ptr+i)); */
    }
    for(int i=0; i<2; i++){
        int tmp = output[i];
        output[i] = output[i+2];
        output[i+2] = tmp;
    }
    printf("%c%c%c%c\n", output[0], output[1], output[2], output[3]);
    /* printf("%s\n", ptr); */

    return 0;
}
