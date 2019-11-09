#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

struct lnode{
    int Src;
    int Dst;
    int Length;
    struct lnode *next;
};

struct lnode *NewNode(){
    struct lnode *node;
    node = (struct lnode*)malloc(sizeof(struct lnode *));
    node->next = NULL;
    return node;
};

int LinkedList_Insert(int Src, int Dst, int Length, struct lnode *head){
    struct lnode *node;
    if(head->next == NULL){
        head->Src = Src;
        head->Dst = Dst;
        head->Length = Length;
    }
    else{
        node = NewNode();
        node->Src = Src;
        node->Dst = Dst;
        node->Length = Length;
        node->next = NULL;
    }
    head->next = node;
    return 0;
}

int main(int argc, char *argv[]){

    struct lnode *head = NULL;
    int Src = 4, Dst = 5, Length = 8;
    head = NewNode();
    LinkedList_Insert(Src, Dst, Length, head);
    /* printf("Linked List Insert Error\n"); */
    /* printf("%lu\n", sizeof(struct lnode *)); */
    printf("%d %d %d\n", head->Src, head->Dst, head->Length);

    return 0;
}
