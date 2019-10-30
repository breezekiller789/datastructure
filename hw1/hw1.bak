#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024
#define SUCCESS 1
#define FAILED -1

//2019.9.15 Q:
//要寫一個getword的程式，把空白濾掉，只取中間的字串，要娶一個字串的時候，
//有兩種方式：
//1、直接malloc一塊夠大的空間來放字串，缺點是浪費空間，可是比較快。
//2、多做一個回圈去看看這個字串有多大，再用這個大小malloc一塊空間來擺，缺點是
//比較慢一些因為要多做回圈，可是比較省空間。
//問看看這兩種做法哪一種比較恰當。
//
//Q : hw1 spec
//
//Q：有沒有什麼方法可以做到動態配置記憶體，在一個未知的輸入資料，不知道這一行
//   會讀入多少資料，該如何宣告？

//Input:
//#rules
//IP1 IP2 action
//#flows
//IP1 IP2

//MINNIE
struct lnode{
    char *Source;
    char *Destination;
    int port;
};

void rmnewline(char *line){
    char *ptr = line;
    while(*ptr && *ptr != '\n')
        ptr++;
    *ptr = '\0';
}

void ParseRule(char *line, FILE *fp, char **Rules, int *offset, char *Rule_Flag){
    while(fgets(line, MaxLine, fp) != NULL){
        rmnewline(line);
        /* printf("line = %s, len = %lu\n", line, strlen(line)); */
        if(strcmp(line, "5\0") == 0){
            if(strcmp(Rule_Flag, "1") == 0)
                break;
            strcpy(Rule_Flag, "1");
            continue;
        }
        *(Rules+*offset) = (char *)malloc(sizeof(char) * strlen(line) + 1);
        strcpy(*(Rules+*offset), line);
        (*offset)++;
    }
}

int getword(char *Flow_Src, char *Flow_Dst, char *Rule_Src, char *Rule_Dst
        , char *line, char *Rules, char *port){
    /* printf("line = %s\n", line); */
    /* printf("word = %s\n", Rules); */
    char *ptr, *qtr, *itr;

    //  拿到Rule的source IP
    ptr = Rules;
    qtr = Rule_Src;
    while(*ptr && !isspace(*ptr)){
        *qtr = *ptr;
        ptr++;
        qtr++;
    }
    *qtr = '\0';

    //  拿到Rule的Destination IP，要先++是因為跳出上個迴圈是遇到不是數字。
    //  所以會是指到空格或者空字元或是tab
    ptr++;
    qtr = Rule_Dst;
    while(*ptr && !isspace(*ptr)){
        *qtr = *ptr;
        ptr++;
        qtr++;
    }
    *qtr = '\0';

    ptr++;
    qtr = port;
    while(*ptr && !isspace(*ptr)){
        *qtr = *ptr;
        ptr++;
        qtr++;
    }
    *qtr = '\0';

    //  拿到Flow的source IP
    ptr = line;
    qtr = Flow_Src;
    while(*ptr && !isspace(*ptr)){
        *qtr = *ptr;
        ptr++;
        qtr++;
    }
    *qtr = '\0';

    //  拿到Flow的Destination IP
    ptr++;
    qtr = Flow_Dst;
    while(*ptr && !isspace(*ptr)){
        *qtr = *ptr;
        ptr++;
        qtr++;
    }
    *qtr = '\0';
    /* printf("Rule_Src = %s\n", Rule_Src); */
    /* printf("Rule_Dst = %s\n", Rule_Dst); */
    /* printf("port = %s\n", port); */
    /* printf("Flow_Src = %s\n", Flow_Src); */
    /* printf("Flow_Dst = %s\n", Flow_Dst); */
    if(Rule_Src == 0 || Rule_Dst == 0 || Flow_Src == 0 || Flow_Dst == 0
            || port == 0){
        return FAILED;
    }
    return SUCCESS;
}

int main(int argc, char *argv[]){
    
    char **Rules;
    char *line, *ptr, Rule_Flag[2] = "0";
    char *Flow_Src, *Flow_Dst, *Rule_Src, *Rule_Dst, *port;
    int offset = 0;
    FILE *fp;
    fp = fopen("input.txt", "r");
    Rules = (char **)malloc(sizeof(char *) * MaxLine);
    line = (char *)malloc(sizeof(char) * MaxLine);

    //  先把Rule都讀進來，放在Rules裡面。
    ParseRule(line, fp, Rules, &offset, Rule_Flag);

    //  再來就是一行一行讀Flow，做相對應的處理。
    //  兩種情況，source IP一樣，或者不一樣，一樣的話，就看Destination IP，
    //  如果又一樣，直接輸出，不一樣就看Rule的Destination是不是don't care，
    //  如果是，就輸出，不一樣的話就看看現在比到最後一個rule了沒，若還沒比完，
    //  就繼續比，比完了就代表完全沒有符合的rule，直接drop。
    //
    //  若source IP不一樣，先看Destinaion IP一不一樣，若一樣，就看Rule的source
    //  是否為don't care，若是don't care，就輸出，若不是don't care，就先檢查比
    //  到最後了沒，若比到最後了，就drop，還沒比到最後的話就繼續比。
    //
    //  若source IP, Destination IP都不一樣，就先看看有沒有兩個都是don't care
    //  ，如果有，就直接輸出，若沒有，就檢查現在是比到最後了沒，若還沒，繼續比
    //  ，如果比到最後了，drop。
    while(fgets(line, MaxLine, fp) != NULL){
        rmnewline(line);
        /* printf("%s\n", line); */
        for(int i=0; i<offset; i++){
            /* printf("=============================\n"); */
            Flow_Src = (char *)malloc(sizeof(char) * strlen(line));
            Flow_Dst = (char *)malloc(sizeof(char) * strlen(line));
            Rule_Src = (char *)malloc(sizeof(char) * strlen(*(Rules+i)));
            Rule_Dst = (char *)malloc(sizeof(char) * strlen(*(Rules+i)));
            port = (char *)malloc(sizeof(char) * strlen(*(Rules+i)));
            if(getword(Flow_Src, Flow_Dst, Rule_Src, Rule_Dst, line
                    , *(Rules+i), port) == -1){
                printf("Somehow getword() FAILED\n");
                continue;
            }
            /* printf("=============================\n"); */
            if(strcmp(Rule_Src, Flow_Src) == 0){
                if(strcmp(Rule_Dst, Flow_Dst) == 0){
                    //  輸出port
                    printf("%s %s %s\n", Flow_Src
                            , Flow_Dst, port);
                    break;
                }
                else if(strcmp(Rule_Dst, "*") == 0){
                    //  Don't Care, 輸出port
                    printf("%s %s %s\n", Flow_Src
                            , Flow_Dst, port);
                    break;
                }
                else{
                    //  check if i is offset-1
                    //  if true, drop, else continue
                    if(i == offset-1){
                        printf("%s %s drop\t\n", Flow_Src
                                , Flow_Dst);
                        break;
                    }
                    else
                        continue;
                }
            }
            else if(strcmp(Rule_Dst, Flow_Dst) == 0){
                if(strcmp(Rule_Src, "*") == 0){
                    //  don't care，輸出port
                    printf("%s %s %s\n", Flow_Src
                            , Flow_Dst, port);
                    break;
                }
                else{
                    //  check if i is offset-1
                    //  if true, drop, else continue
                    if(i == offset-1){
                        printf("%s %s drop\n", Flow_Src
                                , Flow_Dst);
                        break;
                    }
                    else
                        continue;
                }

            }
            else{
                //  check if Rule_Src equals to Rule_Dst,
                //  if true, output port
                //  if not true, drop
                //  else continue to compare
                if(strcmp(Rule_Src, Rule_Dst) == 0
                        && strcmp(Rule_Src, "*") == 0){
                    printf("%s %s %s\n", Flow_Src
                            , Flow_Dst, port);
                    break;
                }
                else if(i == offset-1){
                    printf("%s %s drop\t\n", Flow_Src
                            , Flow_Dst);
                    break;
                }
                else
                    continue;
            }
        }
    }

    return 0;
}
