#include<stdio.h>
int main()
{
    int n,a=1,b=0,i;
    scanf("%d",&n);

    for (i=1;i<=n;++i)
    {
        a*=i;
        b+=a;
    }

    printf("%d %d %d",n,a,b);
}