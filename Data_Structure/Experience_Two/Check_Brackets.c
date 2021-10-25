/* Use Stack to match brackets, written by SuperBart.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#define ERROR 1
#define OK 0

typedef struct stack{
    char data;
    struct stack *next;
}stack,*stackList;

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
    for (int i = 0; i < stack->data - '0'; ++i){
        p = p->next;
    }
    p->next = toPush;
    stack->data += 1;
    return OK;
}

char pop(stackList stack){
    stackList p = stack;
    stackList toPop = NULL;
    for (int i = 0; i < stack->data - '0' - 1; ++i){
        p = p->next;
    }
    int toReturn = p->next->data;
    toPop = p->next;
	p->next = NULL;
    free(toPop);
    stack->data -= 1;
    return toReturn;
}

int isEmpty(stackList stack){
    if (stack->data == '0'){
        return OK;
    } else {
        return ERROR;
    }
}


int main(){
	int situation = 1;
	char line[1000]={'\0'};
	fgets(line,1000,stdin);
	int left = 0, right = 0;
	stackList stack = (stackList)malloc(sizeof(stack));
    if (!stack){
        printf("Unable to Create Stack.\n");
        return ERROR;
    } else {
        stack->data = '0';
        stack->next = NULL;
    }
	for(int i = 0; line[i]!='\n'; ++i){
		if (line[i] == '{' || line[i] == '[' || line[i] == '(' ){
			left++;
		} else if (line[i] == '}' || line[i] == ']' || line[i] == ')' ){
			right++;
		}		
	}
	printf("%d %d\n",left,right);
	for(int i = 0; line[i]!='\n'; ++i){
		if (line[i] == '{' || line[i] == '[' || line[i] == '(' ){
			push(line[i],stack);
		} else if (line[i] == '}' || line[i] == ']' || line[i] == ')' ){
            if (isEmpty(stack) == OK){
                printf("NO");
                situation = 0;
                break;
            }
            
            char top = pop(stack);

			if (top == '{' && line[i] == '}'||
			    top == '[' && line[i] == ']'||
				top == '(' && line[i] == ')' ){
					continue;
				} else {
					printf("NO");
					situation = 0;
					break;
				}
				
		}
	}
	if(isEmpty(stack) == OK && situation != 0){
		printf("YES");
	} else if (isEmpty(stack) == ERROR && situation != 0){
		printf("NO");
	}
}