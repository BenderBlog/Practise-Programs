#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main()
{
    char a[101]={'\0'};
    int number[10];
    int i,j=0,k;
    for (i=0;i<10;++i) number[i]=-1;

    fgets(a,100,stdin);

    for (i=0;i<strlen(a);++i)
    {
        if ( isdigit(a[i])!=0 )
        {
            if (number[j]==-1) number[j]=0;
            number[j] = number[j] * 10 + ( a[i] - '0' );
        }
        else if ( i!=0 && isalpha(a[i])!=0 && isdigit(a[i-1])!=0 )
        {
            j++;
        }
    }

    for (i=0;i<10;++i)
    {
        for (j=i,k=i+1;k<10;++k)
        {
            if (number[k]>number[j]) j=k;
        }
        if (j!=i)
        {
            int temp=number[j];number[j]=number[i];number[i]=temp;
        }
    }

    for (i=0;i<10;++i) if (number[i]!=-1) printf("%d ",number[i]);
}