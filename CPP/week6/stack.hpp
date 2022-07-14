#ifndef STACK
#define STACK

#ifndef IOSTREAM
#include <iostream>
#endif

#include "stack_declearation.hpp"

//自定义栈接口(interface):使用者（用户,user）角度

bool InitStack(Stack &S);

bool isEmpty(Stack S);

ElemType GetTop(Stack S);

bool Push(Stack &S, ElemType e);

void Pop(Stack &S);

/*end of interface */

#endif