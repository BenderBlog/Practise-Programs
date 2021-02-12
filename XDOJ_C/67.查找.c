#include<stdio.h>
int main()
{
    int a[100],n,k,i,count=0;
    
    scanf("%d %d",&n,&k);
    for (i=0;i<n;++i)
    {
        scanf("%d",&a[i]);
    }

    
    for (i=0;i<n;++i)
    {
        if (a[i]==k)
        {
            printf("%d ",i);
            count++;
        }
    }
    if (count==0) printf("-1");

}