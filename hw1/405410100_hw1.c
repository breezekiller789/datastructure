#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024
#define SUCCESS 1
#define FAILED -1

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

void ParseRule(char *line, FILE *Input_File, char **Rules, int *offset, char *Rule_Flag, int N_Rules){
    int idx = 0 ;
    /* printf("N_Rules = %d\n", N_Rules); */
    while(fgets(line, MaxLine, Input_File) != NULL){
        if(idx == N_Rules){
            break;
        }
        rmnewline(line);
        /* printf("line = %s, len = %lu\n", line, strlen(line)); */
        /* if(strcmp(line, "5\0") == 0){ */
        /*     if(strcmp(Rule_Flag, "1") == 0) */
        /*         break; */
        /*     strcpy(Rule_Flag, "1"); */
        /*     continue; */
        /* } */
        *(Rules+*offset) = (char *)malloc(sizeof(char) * strlen(line) + 1);
        strcpy(*(Rules+*offset), line);
        (*offset)++;
        idx++;
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
    int offset = 0, N_Rules = 0, N_Follows = 0, idx=0;
    FILE *Input_File, *Output_File;
    Input_File = fopen("input.txt", "r");
    Output_File = fopen("output.txt", "w");
    Rules = (char **)malloc(sizeof(char *) * MaxLine);
    line = (char *)malloc(sizeof(char) * MaxLine);
    fgets(line, MaxLine, Input_File);
    N_Rules = atoi(line);


    //  先把Rule都讀進來，放在Rules裡面。
    ParseRule(line, Input_File, Rules, &offset, Rule_Flag, N_Rules);

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
    /* printf("%s\n", line); */
    /* fgets(line, MaxLine, Input_File); */
    N_Follows = atoi(line);
    fprintf(Output_File, "%d\n", N_Follows);
    while(fgets(line, MaxLine, Input_File) != NULL){
        if(idx == N_Follows){
            break;
        }
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

            //  Source一樣，往下三個case
            if(strcmp(Rule_Src, Flow_Src) == 0){

                //  完全一模一樣，直接輸出
                if(strcmp(Rule_Dst, Flow_Dst) == 0){
                    //  輸出port
                    /* printf("%s %s %s\n", Flow_Src */
                    /*         , Flow_Dst, port); */
                    fprintf(Output_File, "%s %s %s\n", Flow_Src, Flow_Dst
                            , port);
                    break;
                }
                //  Source一樣，但是Destination是don't care
                else if(strcmp(Rule_Dst, "*") == 0){
                    //  Don't Care, 輸出port
                    /* printf("%s %s %s\n", Flow_Src */
                    /*         , Flow_Dst, port); */
                    fprintf(Output_File, "%s %s %s\n", Flow_Src, Flow_Dst
                            , port);
                    break;
                }
                //  Source一樣，但是Destination不一樣
                //  檢查是不是已經完全都走過了而且都沒有，如果都走完了還是沒有
                //  就是drop，如果還沒走完就繼續走。
                else{
                    //  會進去就是走完了，直接drop
                    //  check if i is offset-1
                    //  if true, drop, else continue
                    if(i == offset-1){
                        /* printf("%s %s drop\t\n", Flow_Src */
                        /*         , Flow_Dst); */
                        fprintf(Output_File, "%s %s drop\n", Flow_Src, Flow_Dst);
                        break;
                    }
                    else
                        continue;
                }
            }
            //  Destination一樣的case
            else if(strcmp(Rule_Dst, Flow_Dst) == 0){
                //  Destination一樣而且Source是don't care，直接輸出
                if(strcmp(Rule_Src, "*") == 0){
                    //  don't care，輸出port
                    /* printf("%s %s %s\n", Flow_Src */
                    /*         , Flow_Dst, port); */
                    fprintf(Output_File, "%s %s %s\n", Flow_Src, Flow_Dst
                            , port);
                    break;
                }
                //  Destination一樣然後Source不一樣，就drop
                else{
                    //  check if i is offset-1
                    //  if true, drop, else continue
                    if(i == offset-1){
                        /* printf("%s %s drop\n", Flow_Src */
                        /*         , Flow_Dst); */
                        fprintf(Output_File, "%s %s drop\n", Flow_Src, Flow_Dst);
                        break;
                    }
                    else
                        continue;
                }

            }
            //  Source是don't care然後Destination有可能一樣或不一樣。
            /* else if(strcmp(Rule_Src, "*") == 0){ */
            /*     //  Source是don't care，然後Destination一樣，就直接輸出 */
            /*     if(strcmp(Rule_Dst, Flow_Dst) == 0){ */
            /*         fprintf(Output_File, "%s %s %s\n", Flow_Src, Flow_Dst */
            /*                 , port); */
            /*         break; */
            /*     } */
            /*     else if(strcmp(Rule_Dst, Rule_Src) == 0){ */
            /*         fprintf(Output_File, "%s %s %s\n", Flow_Src, Flow_Dst */
            /*                 , port); */
            /*         break; */
            /*     } */
            /*     //  Source是don't care然後Destination不一樣，檢查是不是已經走完 */
            /*     //  如果走完了，就是drop，如果沒走完，就繼續走。 */
            /*     else{ */
            /*         //  會進來就代表走到最後了，drop */
            /*         if(i == offset-1){ */
            /*             fprintf(Output_File, "%s %s drop\n", Flow_Src, Flow_Dst); */
            /*             break; */
            /*         } */
            /*         else */
            /*             continue; */
            /*     } */
            /* } */
            /* //  Destination是don't care然後Source有可能一樣或不一樣。 */
            /* else if(strcmp(Rule_Dst, "*") == 0){ */
            /*     //  Destination是don't care然後Source是一樣的，直接輸出。 */
            /*     if(strcmp(Rule_Src, Flow_Src) == 0){ */
            /*         fprintf(Output_File, "%s %s %s\n", Flow_Src, Flow_Dst */
            /*                 , port); */
            /*         break; */
            /*     } */
            /*     else{ */
            /*         //  會進來就代表走到最後了，drop */
            /*         if(i == offset-1){ */
            /*             fprintf(Output_File, "%s %s drop\n", Flow_Src, Flow_Dst); */
            /*             break; */
            /*         } */
            /*         else */
            /*             continue; */
            /*     } */
            /* } */
            else{
                //  check if Rule_Src equals to Rule_Dst,
                //  if true, output port
                //  if not true, drop
                //  else continue to compare
                /* printf("Rule_Src = %s, Rule_Dst = %s\n", Rule_Src, Rule_Dst); */
                if(strcmp(Rule_Src, "*") == 0 && strcmp(Rule_Dst, "*") == 0){
                    /* printf("%s %s %s\n", Flow_Src */
                    /*         , Flow_Dst, port); */
                    fprintf(Output_File, "%s %s %s\n", Flow_Src, Flow_Dst
                            , port);
                    break;
                }
                else if(i == offset-1){
                    /* printf("%s %s drop\t\n", Flow_Src */
                    /*         , Flow_Dst); */
                    fprintf(Output_File, "%s %s drop\n", Flow_Src, Flow_Dst);
                    break;
                }
                else
                    continue;
            }
        }
        idx++;
    }

    return 0;
}
