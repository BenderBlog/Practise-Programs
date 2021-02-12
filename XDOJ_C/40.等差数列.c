#include<stdio.h>
int main()
{
    int n,a[100];
    int i,j,k,temp,d;

    scanf("%d",&n);
    for (i=0;i<n;++i)
    {
        scanf("%d",&a[i]);
    }

    for(i=0;i<n-1;++i)
    {
        for(j=i,k=i+1;k<n;++k)
        {
            if (a[k]<a[j])
            {
                j=k;
            } 
        }
        if (j!=i)
        {
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
    }

    d = a[1] - a[0];
    for (i=1;i<n-1;++i)
    {
        temp = a[i+1] - a[i];
        if (temp!=d)
        {
            printf("no");
            return 0;
        }
    }
    printf("%d",d);
    return 0;
}