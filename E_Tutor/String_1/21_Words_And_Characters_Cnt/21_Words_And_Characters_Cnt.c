#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1687

int main(int argc, char *argv[]){
    char words[MaxLine][MaxLine], line[MaxLine];
    int i=0, Capital[26]={0}, len, offset, Lower_Case[26]={0};

    while(scanf("%s", words[i]) != EOF){
        len = strlen(words[i]);
        for(int j=0; j<len; j++){
            //  大寫
            if(words[i][j]>=65 && words[i][j]<=90){
                offset = words[i][j]-65;
                Capital[offset]++;
            }
            //  小寫
            else if(words[i][j]>=97 && words[i][j]<=122){
                offset = words[i][j]-97;
                Lower_Case[offset]++;
            }
            else
                continue;
        }
        i++;
        /* printf("%s\n", words[i++]); */
    }
    printf("%d\n", i);
    //  Lower Case print
    for(int i=0; i<26; i++){
        if(Lower_Case[i] == 0)
            continue;
        else
            printf("%c : %d\n", 'a'+i, Lower_Case[i]);
    }
    for(int i=0; i<26; i++){
        if(Capital[i] == 0)
            continue;
        else
            printf("%c : %d\n", 'A'+i, Capital[i]);
    }
    

    return 0;
}
