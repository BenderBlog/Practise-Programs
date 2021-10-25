/* Use Stack to transfer decimal to binary, written by SuperBart.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#define ERROR 1
#define OK 0

//We use linear list to implement the stack.
typedef struct stack{
    int data;
    struct stack *next;
}stack,*stackList;

//Push is a lot easier.
int push(int data, stackList stack){
    //Create a new node.
    stackList toPush = (stackList)malloc(sizeof(stack));
    if (!toPush){
        printf("Unable to Create node toPush.\n");
        return ERROR;
    } else {
        toPush->data = data;
        toPush->next = NULL;
    }
    //Add to stack, look for the end of the linear list.
    stackList p = stack;
    for (int i = 0; i < stack->data; ++i){
        p = p->next;
    }
    p->next = toPush;
    stack->data += 1;
    return OK;
}

//Pop basically, del the last element of the linear list.
int pop(stackList stack){
    stackList p = stack;
    stackList toPop = NULL;
    for (int i = 0; i < stack->data - 1; ++i){
        p = p->next;
    }
    int toReturn = p->next->data;
    toPop = p->next;
    free(toPop);
    stack->data -= 1;
    return toReturn;
}

//Long Live Head Nodes!
int isEmpty(stackList stack){
    if (stack->data != 0){
        return OK;
    } else {
        return ERROR;
    }
}

int main(){
    int decimal;
    scanf("%d",&decimal);
    //Create Stack, which is based on linear list.
    //This is a head.
    stackList stack = (stackList)malloc(sizeof(stack));
    if (!stack){
        printf("Unable to Create Stack.\n");
        return ERROR;
    } else {
        stack->data = 0;
        stack->next = NULL;
    }
    if (decimal != 0){
    //for (decimal = 0; decimal<=100; ++decimal){
        //Dec to Bin
        int temp = decimal;
        while(temp > 0){
            push(temp % 2,stack);
            temp = temp / 2;
        }
        //Output solution
        while(isEmpty(stack) == OK){
            printf("%d",pop(stack));
        }
        printf(" ");
        //Dec to Octal
        temp = decimal;
        while(temp > 0){
            push(temp % 8,stack);
            temp = temp / 8;
        }
        //Output solution
        while(isEmpty(stack) == OK){
            printf("%d",pop(stack));
        }
        printf(" ");
        //Dec to Hex
        temp = decimal;
        while(temp > 0){
            push(temp % 16,stack);
            temp = temp / 16;
        }
        //Output solution
        while(isEmpty(stack) == OK){
            int check = pop(stack);
            switch(check){
                case 10: printf("A");break;
                case 11: printf("B");break;
                case 12: printf("C");break;
                case 13: printf("D");break;
                case 14: printf("E");break;
                case 15: printf("F");break;
                default: printf("%d",check);
            }
        }
        //printf(" %d\n",decimal);
    } else {
        printf("0 0 0");
    }
    return 0;
}