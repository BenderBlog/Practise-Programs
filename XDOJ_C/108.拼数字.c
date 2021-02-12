#include<stdio.h>
#include<string.h>

int pow_int(int a,int b)
{
    int i,result=1;
    for (i=1;i<=b;++i) result*=a;
    return result;
}

int isPrime(int a)
{
    int i;
    for (i=2;i<=a;++i) if (a%i==0) return 0;
    return 1;
}

int max(int a)
{
    int i;
    for (i=a-1;i>=2;--i)
    {
        if (a%i==0) return i;
    }
    return a;
}

int main()
{
    char a[100],number[100];
    int sum=0,i,bits=0;

    fgets(a,100,stdin);

    for (i=strlen(a)-1;i>=0;--i)
    {
        if ( a[i]>='0' && a[i]<='9' )
        {
            number[bits]=a[i]-'0';
            bits++;
        }
    }

    for (i=0;i<bits;++i)
    {
        sum += number[i] * pow_int(10,i);
    }

    if ( isPrime(sum)==1 || sum==0 )  printf("%d",sum);
    else printf("%d",max(sum));
}