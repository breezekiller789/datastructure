#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

int main(int argc, char *argv[]){

    char line[10], good[10], haha[10];
    scanf("%s %s %s", line, good, haha);
    printf("%s %s %s\n", line, good, haha);

    return 0;
}
