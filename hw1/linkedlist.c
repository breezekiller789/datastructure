#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024
#define SUCCESS 1
#define FAILED 0

struct lnode{
    char *Source;
    char *Destination;
    int port;
    struct lnode *next;
};

struct gnode{
    char *word;
    struct gnode *next;
};

struct gnode *NewNode(){
    struct gnode *node;
    node = (struct gnode *)malloc(sizeof(struct gnode));
    node->next = NULL;
    return node;
};

/* int ParseLine(char *line, char *Src, char *Dst, int Port){ */
/*     char *ptr, *qtr; */
/*     ptr = line; */
/*     qtr = Src; */
/*     while(isdigit(*ptr)){ */
/*         *qtr = *ptr; */
/*         ptr++; */
/*         qtr++; */
/*     } */
/*     *qtr = '\0'; */

/* } */

void rmnewline(char *line){
    char *ptr = line;
    while(*ptr && *ptr != '\n')
        ptr++;
    *ptr = '\0';
}

int main(int argc, char *argv[]){
    struct gnode *head, *node;
    char *line, *Src, *Dst;
    int Port;
    head = NewNode();
    node = head;
    line = (char *)malloc(sizeof(char) * MaxLine);
    while(fgets(line, MaxLine, stdin) != NULL){
        rmnewline(line);
        node->word = (char *)malloc(sizeof(char) * strlen(line) + 1);
        strcpy(node->word, line);
        node->next = NewNode();
        node = node->next;
        /* if(ParseLine(line, Src, Dst, Port) == FAILED){ */
        /*     continue; */
        /* } */
    }
    for(node=head; node->next != NULL; node=node->next){
        printf("%s\n", node->word);
    }

    return 0;
}
