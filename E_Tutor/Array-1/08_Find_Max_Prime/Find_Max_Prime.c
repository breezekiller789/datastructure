#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024
#define YES 1
#define NO 0

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1769

int Determin(int Input_Num){
    int Divider = 1, cnt=0;
    while(Divider <= Input_Num+1){

        //  整除了，就進去。
        if(Input_Num%Divider == 0){
            cnt++;
        }
        Divider++;
    }
    if(cnt==2)
        return YES;
    else
        return NO;
}

int rmnewline(char *line){
    char *ptr = line;
    int len = 0;
    while(*ptr && *ptr != '\n'){
        ptr++;
        len++;
    }
    *ptr = '\0';
    return len;
    /* printf("len = %d\n", len); */
}

int main(int argc, char *argv[]){
    
    int Input_Num, Divider=1, len, cnt, i, j;
    char line[20], word[20], *ptr, *qtr;
    scanf("%s", line);
    len = rmnewline(line);
    cnt = len;
    //  拿到字串長度之後給cnt，待會就是cnt來算現在字串的長度。
    while(cnt > 0){
        //  都是從頭開始，終止條件就是今天子字串超過原字串。
        for(i=0; i+cnt<=len; i++){
            ptr = line;
            ptr = &ptr[i];
            qtr = word;
            for(j=0; j<cnt; j++){
                *qtr = *ptr;
                ptr++;
                qtr++;
            }
            *qtr = '\0';

            //  Debug用
            /* printf("qtr = %s\n", word); */
            /* sleep(3); */

            //  送去判斷這個數是不是質數，會進去就是質數。
            if(Determin(atoi(word))){
                printf("%s\n", word);
                exit(1);
            }
        }
        cnt--;
    }
    if(cnt == 0){
        printf("No Prime Found!\n");
    }

    return 0;
}
