#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=3077

int rmnewline(char *line){
    char *ptr = line, len=0;
    while(*ptr && *ptr != '\n'){
        ptr++;
        len++;
    }
    *ptr = '\0';
    return len;
}

int main(int argc, char *argv[]){

    char *line, *ptr;
    int Shift_Amount, len, i;
    line = (char *)malloc(sizeof(char) * MaxLine);

    fgets(line, MaxLine, stdin);
    len = rmnewline(line);
    ptr = line;
    scanf("%d", &Shift_Amount);

    //  要避免輸入超過26，直接取餘數就好。
    Shift_Amount = Shift_Amount%26;

    i=0;
    while(i<=len){
        if(!isspace(*(ptr+i)) && isalpha(*(ptr+i))){
            //  要分開做，分成大寫跟小寫來做。
            if(*(ptr+i) >= 97){
                //  後面那一塊是在做offset，先算出距離小寫a多遠，算出來之後加上
                //  shift amount，這樣加起來可能還是會超過26，所以還是要取餘數
                ptr[i] = 'a' + ((*(ptr+i)-97)+Shift_Amount)%26;
                i++;
            }
            else{
                //  大寫的case一樣如法炮製。
                ptr[i] = 'A' + ((*(ptr+i)-65)+Shift_Amount)%26;
                i++;
            }
        }
        else{
            i++;
            continue;
        }
    }
    printf("%s\n", ptr);

    return 0;
}
