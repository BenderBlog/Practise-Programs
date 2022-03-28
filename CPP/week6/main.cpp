// Compile using:
//      gcc main.cpp stack.cpp -lstdc++ -o a.out
//
#include "stack.hpp"

int main()

{ //自定义栈测试

    Stack S1;
    ElemType e;
    if (!InitStack(S1))
        return -1;

    Push(S1, 10);
    Push(S1, 20);
    Push(S1, 30);

    while (!isEmpty(S1))
    {
        e = GetTop(S1);
        Pop(S1);
        std::cout << e << std::endl;
    }

    return 0;
}
