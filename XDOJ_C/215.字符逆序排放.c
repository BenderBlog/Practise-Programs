#include<stdio.h>
void fun(char a[],int b)
{
    for (b;b>=0;--b)
    {
        printf("%c",a[b]);
    }
    printf("\n");
    return 0;
}

int main()
{
    char a[100]={0};
    int i=0;
    for (i=0;i<=100;++i)
    {
        scanf("%c",&a[i]);
        if (a[i]=='\n') break;
    }
    //printf("%c %c",a[1],b[1]);
    fun(a,i);
}