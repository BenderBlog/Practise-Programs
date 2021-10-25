/* Use Stack to solve maze, written by SuperBart.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#define ERROR 1
#define OK 0

typedef struct stack{
    int x;
    int y;
    struct stack *next;
}stack,*stackList;

stackList init(stackList stack){
    stack = (stackList)malloc(sizeof(stack));
    if (!stack){
        printf("Unable to Create Stack.\n");
    } else {
        stack->x = 0;
        stack->y = 0;
        stack->next = NULL;
    }
    return stack;
}

int push(int x, int y, stackList stack){
    //Create a new node.
    stackList toPush = (stackList)malloc(sizeof(stack));
    if (!toPush){
        printf("Unable to Create node toPush.\n");
        return ERROR;
    } else {
        toPush->x = x;
        toPush->y = y;
        toPush->next = NULL;
    }
    //Add to stack, look for the end of the linear list.
    stackList p = stack;
    for (int i = 0; i < stack->x; ++i){
        p = p->next;
    }
    p->next = toPush;
    stack->x += 1;
    return OK;
}

void pop(stackList stack){
    stackList p = stack;
    for (int i = 0; i < stack->x - 1; ++i){
        p = p->next;
    }
    stackList toPop = p->next;
    free(toPop);
    stack->x -= 1;
}

stackList gettop(stackList stack){
    stackList p = stack;
    for (int i = 0; i < stack->x - 1; ++i){
        p = p->next;
    }
    stackList toReturn = (stackList)malloc(sizeof(stack));
    toReturn->x = p->next->x;
    toReturn->y = p->next->y;
    toReturn->next = NULL;
    return toReturn;
}

int isEmpty(stackList stack){
    if (stack->x == 0){
        return OK;
    } else {
        return ERROR;
    }
}

int List (stackList L){
    stackList p = L->next;
    int number = L->x;
    if ( number == 0 ){
        printf("empty list!");
    }
    for ( int i = 0; i < number; ++i ){
        int e,f;
        e = p->x;
        f = p->y;
        printf("(%d,%d)",e,f);
        p = p->next;
    }
    return OK;
}

int main(){
    //input maze
    int maze[10][10]={0};
    int size;
    scanf("%d",&size);
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            scanf("%d",&maze[i][j]);
        }
    }
    //eval maze
    int i = 1, j = 1;
    stackList stack = init(stack);
    push(i,j,stack);
    while(1){
        //check if accessable
        //need to change the order
        if(maze[i][j+1]==0){
            maze[i][j+1]=2;
            j++;
            push(i,j,stack);
        } else if(maze[i+1][j]==0){
            maze[i+1][j]=2;
            i++;
            push(i,j,stack);
        } else if(maze[i-1][j]==0){
            maze[i-1][j]=2;
            i--;
            push(i,j,stack);
        } else if(maze[i][j-1]==0){
            maze[i][j-1]=2;
            j--;
            push(i,j,stack);
        } else {
            //not accessful fallback
            if (isEmpty(stack) == ERROR){
                maze[gettop(stack)->x][gettop(stack)->y] = 1;
                pop(stack);
                i = gettop(stack)->x;
                j = gettop(stack)->y;
            }
        }
        //eval solution
        if (gettop(stack)->x == size - 2 && gettop(stack)->y == size - 2){
            List(stack);
            break;
        }
        if (gettop(stack)->x == 1 && gettop(stack)->y == 1){
            printf("NO");
            break;
        }
    }
}
