#include "stack.hpp"

//自定义栈实现(implementation)

bool InitStack(Stack &S)
{
    S.top = nullptr;
    return true;
}

bool isEmpty(Stack S)
{
    return (S.top == nullptr);
}

ElemType GetTop(Stack S)
{
    return S.top->data;
}

bool Push(Stack &S, ElemType e)
{
    NodePTR p = (NodePTR)malloc(sizeof(struct Snode));
    if (!p)
        return false;
    p->data = e;
    p->next = S.top;
    S.top = p;
    return true;
}

void Pop(Stack &S)
{
    NodePTR p = S.top;
    S.top = S.top->next;
    free(p);
}

/*end of linklisted stack implementation */