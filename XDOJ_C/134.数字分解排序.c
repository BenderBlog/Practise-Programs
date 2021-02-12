#include<stdio.h>
#include<string.h>

int pow_int (int a, int b)
{
    int i,c=1;
    for (i=0;i<b;++i)
    {
        c*=a;
    }
    return c;
}

int main()
{
    int i,j,k;
    char a[9]={0};

    scanf("%s",a);
    
    for (i=0;i<strlen(a);++i)
    {
        for (j=i,k=i+1;k<strlen(a);++k)
        {
            if (a[k]-'0'>a[j]-'0') j=k;
        }
        if (j!=i)
        {
            int temp=a[j];a[j]=a[i];a[i]=temp;
        }
    }

    for (i=0;i<strlen(a);++i)
    {
        printf("%c ",a[i]);
    }
    
}