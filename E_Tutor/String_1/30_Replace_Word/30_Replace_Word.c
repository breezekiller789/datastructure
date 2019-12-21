#include <stdio.h>
#include <string.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=2172

void rmnewline(char line[MaxLine]){
    int i=0;
    while(line[i] != '\n')
        i++;
    line[i] = '\0';
}

int main(int argc, char **argv){
    char line[MaxLine], Copystring[MaxLine], target[MaxLine], source[MaxLine];
    char *ptr, *tmp, *cut;
    int i;
    for(i=0; i<3; i++){
        if(i==0){
            fgets(line, MaxLine, stdin);
        }
        else if(i==1){
            fgets(source, MaxLine, stdin);
            rmnewline(source);
        }
        else{
            fgets(target, MaxLine, stdin);
            rmnewline(target);
        }
    }
    rmnewline(line);
    tmp = line;
    while((tmp = cut = strstr(tmp, source))){
        i=0;
        while(source[i] == *tmp && *tmp != '\0'){
            i++;
            tmp++;
        }
        strcpy(Copystring, tmp);
        *cut = '\0';
        strcat(line, target);
        strcat(line, Copystring);
        cut += strlen(target);
        tmp = cut;
    }
    printf("%s\n", line);
    return 0;
}
