#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1906

void rmnewline(char *line){
    char *ptr = line;
    while(*ptr && *ptr != '\n')
        ptr++;
    *ptr = '\0';
}

int main(int argc, char *argv[]){

    int Numbers[10]={0}, i=0, input_cnt=0;
    char line[20], *ptr;
    fgets(line, MaxLine, stdin);
    rmnewline(line);
    ptr = line;
    //  把input吃進來，擺進Numbers的array
    while(*ptr){
        if(isdigit(*ptr)){
            /* printf("*ptr = %d\n", atoi(ptr)); */
            Numbers[i++] = atoi(ptr);
            input_cnt++;
            ptr++;
            continue;
        }
        else
            ptr++;
    }
    char Max[input_cnt+1], Min[input_cnt+1], cnt=0;
    while(cnt < 2){
        if(cnt == 0){
            for(i=0; i<input_cnt; i++){
                for(int j=0; j<input_cnt-1-i; j++){
                    if(Numbers[j] > Numbers[j+1]){
                        int tmp = Numbers[j];
                        Numbers[j] = Numbers[j+1];
                        Numbers[j+1] = tmp;
                    }
                }
            }
            cnt++;
            for(i=0; i<input_cnt; i++){
                sprintf(&Min[i], "%d", Numbers[i]);
            }
            /* printf("%s\n", Max); */
        }
        else{
            for(i=0; i<input_cnt; i++){
                for(int j=0; j<input_cnt-1-i; j++){
                    if(Numbers[j] < Numbers[j+1]){
                        int tmp = Numbers[j];
                        Numbers[j] = Numbers[j+1];
                        Numbers[j+1] = tmp;
                    }
                }
            }
            cnt++;
            for(i=0; i<input_cnt; i++){
                sprintf(&Max[i], "%d", Numbers[i]);
            }
            /* printf("%s\n", Min); */
        }
    }
    printf("Max = %s, Min = %s\n", Max, Min);
    int Max_Num = atoi(Max);
    int Min_Num = atoi(Min);
    printf("%d\n", Max_Num-Min_Num);

    return 0;
}
