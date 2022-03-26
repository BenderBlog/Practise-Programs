#include<stdio.h>
void fun(char a[],char b[])
{
    int i=0,j=0,k=0;
    char c[200]={0};
    for (i;a[i]!='\n';++i)
    {
        c[i] = a[i];
    }
    for (j=0;b[j]!='\n';++j)
    {
        c[i+j] = b[j];
    }
    while (c[k]!=0)
    {
        printf("%c",c[k]);
        ++k;
    }
    printf("\n");
    return 0;
}

int main()
{
    char a[100]={0},b[100]={0};
    int i=0,j=0;
    for (i=0;i<=100;++i)
    {
        scanf("%c",&a[i]);
        if (a[i]=='\n') break;
    }
    for (j=0;j<=100;++j)
    {
        scanf("%c",&b[j]);
        if (b[j]=='\n') break;
    }
    //printf("%c %c",a[1],b[1]);
    fun(a,b);
}