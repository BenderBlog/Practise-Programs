#include<stdio.h>
int main ()
{
    int n[100]={0},i,j,k,round,temp;
    scanf("%d",&round);
    for (i=0;i<round;++i)
    {
        scanf("%d",&n[i]);
    }

    for (i=0;i<round;++i)
    {
        for (j=i,k=i+1;k<round;++k)
        {
            if (n[j]%2==1 && n[k]%2==0)
            {
                j=k;
            }
        }
        if (j!=i)
        {
            temp=n[j];n[j]=n[i];n[i]=temp;
        }
    }
    for (i=0;i<round;++i) printf("%d ",n[i]);
    printf("\n");

    for (i=0;i<round;++i)
    {
        for (j=i,k=i+1;k<round;++k)
        {
            if (n[j]<n[k] && (n[j]%2==n[k]%2)) j=k;
        }
        if (j!=i)
        {
            temp=n[j];n[j]=n[i];n[i]=temp;
        }
    }

    for (i=0;i<round;++i) printf("%d ",n[i]);
}