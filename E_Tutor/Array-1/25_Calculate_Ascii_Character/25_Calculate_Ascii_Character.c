#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024
#define Ascii_Size (1<<7)-1

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=2435

int main(int argc, char *argv[]){

    char character[Ascii_Size];
    int array[Ascii_Size]={0}, i=0, c;
    while((c = getchar()) != EOF){
        if(c<32 || c>127)
            continue;
        /* printf("%d\n", c); */
        array[c]++;
        character[c] = (char)c;
    }
    for(i=0; i<Ascii_Size; i++){
        if(array[i] == 0){
            continue;
        }
        else{
            printf("%d %d\n", i, array[i]);
        }
    }
    

    return 0;
}
