/* A Single LinkList demo written by SuperBart.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#define ERROR 1
#define OK 0

/* Defination of Single LinkList:
 *   In convinement of understanding, integer is chosen to be used as ElementType.
 *   Two Parts in the node of LinkList, the data, and the point to the next node.
 *   The first node is the head node, stored the number of the node in the data.
 *   The last node's point is set to NULL.
 */
typedef int ElementType;
typedef struct Node{
    ElementType data;
    struct Node *next;
}Node, *LinkList;

/* Function: Initalize the LinkList.
 * Note here:
 *   The Linklist created here do not return to formula 'main'.
 *   Somebody recommend me to use &L and use cpp, but I don't want to.
 *   Because I know nothing about cpp, and I want to know something only
 *   if I know entirely.
 *   So the formula here has been transfered to formula 'main'.
 *   Further comment would be written in formula 'main'.
 *   Neh. Maggie is cuter than Flandre;-) 
int CreateList (LinkList L){
    L = (LinkList)malloc(sizeof(Node));
    if (!L) {
        printf("Unable to Create List L.\n");
        return ERROR;
    } else {
        L->data = 0;
        L->next = NULL;
        return OK;
    }
}*/

// Function: Add node 'toadd' to the postition of the LinkList.
int AddNode (LinkList L, int position, ElementType toadd){

    LinkList p = L; // A point p, used to search node in LinkList L.
    int mark = 0;   // Store the position.

    // Search for the position's previous node.
    while ( p != NULL && mark < position - 1 ){
        p = p->next; mark++;
    }

    // If position we need is not found, it's time to exit the chaos.
    if ( p == NULL || mark > position - 1 ){
        printf("Unable to add!");
        return ERROR;
    }

    // Create a node 'add', write toadd to add's data.
    // Position's previous node's next point shall be set to add.
    // Add's next, naturally, is position's node.
    // Add 1 to the first node's data.
    LinkList add = (LinkList)malloc(sizeof(Node));
    add->data = toadd;
    add->next = p->next;
    p->next = add;
    L->data += 1;
    return OK;
}

// Function: Delete a Node in the LinkList.
// Must similar to the previous.
int DelNode (LinkList L, int position){

    LinkList p = L;
    int mark = 0;

    while ( p != NULL && mark < position - 1 ){
        p = p->next; mark++;
    }

    if ( p == NULL || mark > position - 1 ){
        printf("Unable to del!");
        return ERROR;
    }

    // Position's previous node's next point shall be set to position's next.
    // Free the node to be delete, which stored in the 'del'.
    // Minus 1 to the first node's data.
    LinkList del = (LinkList)malloc(sizeof(Node));
    del = p->next;
    p->next = del->next;
    del->next = NULL;
    free(del);
    L->data -= 1;
    return OK;
}

// Function: List all the node in the LinkList.
int ListNode (LinkList L){
    LinkList p = L->next;
    int number = L->data;
    if ( number == 0 ){
        printf("empty list!");
    }
    for ( int i = 0; i < number; ++i ){
        ElementType e;
        e = p->data;
        printf("%d ",(int)e);
        p = p->next;
    }
    printf("\n");
    return OK;
}

// Demo Only, formula up here.
// Evil Smile from Mr Burns.
int main() {
    // Following Lines are used to create LinkList.
    // The data in the first node ("the head node") stored the number of the node.
    LinkList L = (LinkList)malloc(sizeof(Node));
    if (!L) {
        printf("Unable to Create List L.\n");
        return ERROR;
    } else {
        L->data = 0;
        L->next = NULL;
    }
    // Add Node
    int toAdd;
    scanf("%d",&toAdd);
    while(toAdd != 0){
        AddNode(L,1,toAdd);
        scanf("%d",&toAdd);
    }
    ListNode(L);
    // Del Node
    int number = L->data;
    for (int i = 0; i < number; ++i){
        DelNode(L,1);
        ListNode(L);
    }
    return OK;
}