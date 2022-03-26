//2021 SuperBart@Bilibili Under CC-BY-SA
//程序课程作业2 堆栈模拟 本程序模拟了十个堆栈
//堆栈简单来说就是：先进的后出去，只能对最上面的元素进行处理
//魔改自ZouHuiDong@CSDN的代码，原链接：https://blog.csdn.net/ZouHuiDong/article/details/90343026

#include <stdio.h>

struct stack
{                   
    char stack[10]; //栈数组，一共有10个元素
    int head;       //栈的头，默认为0，表示堆栈中没有元素
} Stack;

//输出堆栈状态
void show()
{
    printf("====目前堆栈状态====\n");
    for (int i = 9; i >= 0; i--)
        printf("[%c]\n", Stack.stack[i]);
}

int main()
{
    printf("本程序模拟10个堆栈，堆栈元素用字符代替\n");    
    //以下对堆栈进行初始化
    for (int i = 0; i < 11; ++i)
        Stack.stack[i] = 0;
    Stack.head = 0;
    show();

    while (1)
    {
        //提示终端，接受用户输入
        int arg = 0;
        printf("按1入栈，按2出栈，按3返回栈顶元素，按4退出：");
        scanf("%d", &arg);

        if (arg == 1)
        {
            int number = 0;
            //输入入栈元素个数，包括溢出判断
            while (1)
            {
                printf("请输入入栈元素个数：");
                getchar();  //输入可能会有回车残留，拿这个接一下，以下同理
                scanf("%d", &number);
                if (number + Stack.head <= 10)
                    break;
                else
                    printf("无效，会过栈顶\n");
            }
            //此处循环输入堆栈元素，这里用一个字符代替
            //这里我想一股气都输入，可是回车总是给我捣乱
            printf("要入栈%d个元素，请输入栈元素：\n", number);
            for (int i = 0; i < number; ++i)
            {
                printf("    第%d个栈元素：", i + 1);
                getchar();
                scanf("%c", &Stack.stack[Stack.head]);
                Stack.head++;   //改变栈顶位置
            }

            show();
        }

        else if (arg == 2)
        {
            int number = 0;
            //输入入栈元素个数，包括触底判断
            while (1)
            {
                printf("请输入出栈元素个数：");
                getchar();
                scanf("%d", &number);
                if (Stack.head - number < 0)
                    printf("无效，会过栈底\n");
                else
                    break;
            }
            //将出栈元素按序放在output数组中
            char output[10] = {'\0'};
            for (int i = 0; i < number; ++i)
            {
                Stack.head--;
                output[i] = Stack.stack[Stack.head];
                Stack.stack[Stack.head] = '\0';
            }

            show();
            printf("输出元素有：");
            for (int i = 0; output[i] != '\0'; ++i)
                printf("[%c]", output[i]);
            printf("\n");
        }

        else if (arg == 3)
        {
            show();
            if (Stack.stack[0] == '\0')
                printf("栈中没有元素:-(\n");
            else
                printf("栈顶元素：[%c]\n", Stack.stack[Stack.head - 1]);
        }

        else if (arg == 4)
        {
            break;
        }

        else
        {
            printf("无效选项:-(\n");
            continue;
        }
    }

    return 0;
}