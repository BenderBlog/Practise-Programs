/* Simple stack using array, using as a header file. 
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */

/* Element in the stack is Integer.
 * I believe it is pretty protable:-P
 */

#ifndef _STACK_H_
#define _STACK_H_

#ifndef _STDIO_H
#include<stdio.h>
#endif

#ifndef _STDLIB_H
#include<stdlib.h>
#endif

#ifndef _STDBOOL_H
#include<stdbool.h>
#endif

/* Brief introduction of the things in this header file. */
typedef struct array_stack stack;
stack initStack(int numbers);
stack pop(stack toPop);
stack push(stack toPush, int element);
int gettop(stack toGet);
bool isEmpty(stack toEval);

/* Stack implement using array, easier to code. */
typedef struct array_stack{
    int numbers;
    int top;
    int *element;
}stack;

/* Generate a new stack, size based on numbers. */
stack initStack(int numbers){
    stack toReturn;
    toReturn.numbers = numbers;
    toReturn.top = 0;
    toReturn.element = (int *)calloc(toReturn.numbers + 1,sizeof(int));
    return toReturn;
}

/* Pop out the top element of the stack. */
stack pop(stack toPop){
    if (toPop.top == 0){
        printf("Stack empty.\n");
    } else {
        toPop.element[toPop.top] = 0;
        toPop.top = toPop.top - 1;
    }
    return toPop;
}

/* Push a new element to the stack. */
stack push(stack toPush, int element){
    if (toPush.top == toPush.numbers){
        printf("Stack Full!\n");
    } else {
        toPush.top = toPush.top + 1;
        toPush.element[toPush.top] = element;
    }
    return toPush;
}

/* Get the element at the top of the stack. */
int gettop(stack toGet){
    if (toGet.top == 0){
        printf("Stack empty.\n");
        return -1;
    } else {
        return toGet.element[toGet.top];
    }
}

bool isEmpty(stack toEval){
    if (toEval.top == 0){
        return true;
    } else {
        return false;
    }
}

#endif