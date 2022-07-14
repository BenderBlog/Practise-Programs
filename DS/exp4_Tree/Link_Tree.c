/* binTree Demo.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERROR 1
#define OK 0


// binTree

/* A Basic BinTree includes three things--
 *      a. data
 *      b. two arraies, to his left/right child.
 */
typedef struct Element{
    char data;
    struct Element *leftChild;
    struct Element *rightChild;
}Element, *binTree;

// stack

typedef struct stack{
    binTree dealing;
    int outLine;
    struct stack *next;
}stack,*stackList;

// stack
stackList initStack(stackList stack){
    stack = (stackList)malloc(sizeof(stack));
    if (!stack){
        printf("Unable to Create Stack.\n");
    } else {
        stack->dealing = NULL;
        stack->outLine = 0;
        stack->next = NULL;
    }
    return stack;
}

int push(binTree dealt, stackList stack){
    //Create a new node.
    stackList toPush = (stackList)malloc(sizeof(stack));
    if (!toPush){
        printf("Unable to Create node toPush.\n");
        return ERROR;
    } else {
        toPush->dealing = dealt;
        toPush->outLine = 0;
        toPush->next = NULL;
    }
    //Add to stack, look for the end of the linear list.
    stackList p = stack;
    for (int i = 0; i < stack->outLine; ++i){
        p = p->next;
    }
    p->next = toPush;
    stack->outLine += 1;
    return OK;
}

void pop(stackList stack){
    stackList p = stack;
    for (int i = 0; i < stack->outLine - 1; ++i){
        p = p->next;
    }
    stackList toPop = p->next;
    free(toPop);
    stack->outLine -= 1;
}

stackList gettop(stackList stack){
    stackList p = stack;
    for (int i = 0; i < stack->outLine; ++i){
        p = p->next;
    }
    return p;
}


binTree InitTree (binTree L, char *toInit){
    // Create BinTree's ROOT.
    L = (binTree)malloc(sizeof(Element));
    if (!L) {
        printf("Unable to Create Tree L's Entry.\n");
        return NULL;
    } else {
        L->data = '\0';
        L->leftChild = NULL;
        L->rightChild = NULL;
    }
    // Point to travel and work.
    binTree p = L;
    // Stack to make everything great again.
    stackList process = initStack(process);
    stackList a = process;
    // Evaling. '.' refer to nothing.
    // And what? No entey point of the BinTree.
    for (int i = 0; i < strlen(toInit); ++i){
        char processing = toInit[i];
        printf("%c",processing);
        if ( i == 0 ){
            p->data = toInit[i];
            push(p,process);
            a = a->next;
        } else if ( toInit[i] == '.' ){
            a->outLine += 1;
        } else {
            binTree toAdd = (binTree)malloc(sizeof(Element));
            toAdd->data = toInit[i];
            toAdd->leftChild = NULL;
            toAdd->rightChild = NULL;
            if (a->outLine == 0){
                p->leftChild = toAdd;
                p = p->leftChild;
            } else if (a->outLine == 1){
                p->rightChild = toAdd;
                p = p->rightChild;
            }
            a->outLine += 1;
            push(p,process);
            a = a->next;
        }
        while (a->outLine == 2){
            pop(process);
            a = gettop(process);
            p = a->dealing;
        }
    }
    return L;
}

// Pre-Order ROOT-LEFT-RIGHT
void first(binTree T){
    if(T){
	   printf("%c",T->data);
	   first(T->leftChild);
	   first(T->rightChild);
	}
	return;
}

// Mid-Order LEFT-ROOT-RIGHT
void mid(binTree T){
	if(T){
		mid(T->leftChild);
		printf("%c",T->data);
		mid(T->rightChild);
	}
}

// Post-Order LEFT-RIGHT-ROOT
// Refrence Website: https://www.cnblogs.com/SHERO-Vae/p/5800363.html
void last(binTree T){
    // Store the Element to be Output.
    stackList order = (stackList)malloc(sizeof(stackList));
    binTree cur = T;           // Point to travel and work.
    binTree pre=NULL;          // Previous travelled node.
    // Push the root in the stack, since last output.
    push(cur,order);
    while(order->outLine != 0)
    {
        cur=gettop(order)->dealing;

        if((cur->leftChild==NULL&&cur->rightChild==NULL)||
           (pre!=NULL&&(pre==cur->leftChild||pre==cur->rightChild))){
            // No Child or Child are read.
            printf("%c",cur->data);
            pop(order);
            pre=cur;
        } else {
            // Right first push, then left.
            if(cur->rightChild!=NULL)
                push(cur->rightChild,order);
            if(cur->leftChild!=NULL)
                push(cur->leftChild,order);
        }
    }
}

/* How to save time 233
void last(binTree T)
{
	if(T){
		last(T->leftChild);
		last(T->rightChild);
		printf("%c",T->data);
	}
}
*/

int main(){
    char a[] = "AB.C..DE..FG.I..H..";
    binTree L = InitTree(L,a);
    printf("\nFirst Order\n");
    first(L);
    printf("\nMid Order\n");
    mid(L);
    printf("\nLast Order\n");
    last(L);
    printf("\nFinished\n");
    return 0; 
}

