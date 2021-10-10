/* A Exhanced Bubble Sort Demo using LinkList
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#define ERROR 1
#define OK 0

/* Purpose: Text Order formula. In order to use it in MultiPolynomial program.
 * And since it's part of the questiona, why not upload it.
 * Also, curse those people who just copy my code written with headache.
 */ 

// Defination of Node
// Note that the 'head node' stores the numbers of the node.
typedef struct Node{
    int data;
    struct Node *next;
}Node, *LinkList;

// Add Node Formula, copied from Linear_List.c, which also written by me.
int AddNode (LinkList L, int position, int toadd){
    LinkList p = L;
    int mark = 0;
    while ( p != NULL && mark < position - 1 ){
        p = p->next; mark++;
    }
    if ( p == NULL || mark > position - 1 ){
        printf("Unable to add!");
        return ERROR;
    }
    LinkList add = (LinkList)malloc(sizeof(Node));
    add->data = toadd;
    add->next = p->next;
    p->next = add;
    L->data += 1;
    return OK;
}

/* A Exhanced Bubble Sort.
 *     a. Search for each node.
 *     b. In each node, search for *the later node*, remember the biggest node.
 *     c. Of course, we need to change the material in the node.
 *        Not the whole node, just the material.
 * First semester of the college.
 * Though still not the quickest...:-P
 */
int Order(LinkList L){
    // Point for (a)
    LinkList p = L->next;
    // Round, look for (a).
    for ( int i = 0; i < L->data - 1; ++i ){
        // Point for (b)
        LinkList q = p->next;
        // Store the biggest node (b)
        LinkList max = p;
        // Round in the round, (b)
        for ( int j = i; j < L->data - 1; ++j ){
            // If found the bigger, change max. Then go to the next.
            if ( max->data < q->data ){
                max = q;
            }
            q = q->next;
        }
        // Step (c), neh.
        if ( max->data != p->data ){
            int temp;
            temp = max->data;
            max->data = p->data;
            p->data = temp;
        }
        p = p -> next;
    }
}

// List all the node in the LinkList.
// Copied from Linear_List.c, which also written by me.
int ListNode (LinkList L){
    LinkList p = L->next;
    int number = L->data;
    if ( number == 0 ){
        printf("empty list!");
    }
    for ( int i = 0; i < number; ++i ){
        int e;
        e = p->data;
        printf("%d ",(int)e);
        p = p->next;
    }
    printf("\n");
    return OK;
}

// Demo Only, formula up here.
// Whaaaaaaa.
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
    // Order Node
    Order(L);
    ListNode(L);
    return OK;
}