#include<stdio.h>
int main ()
{
    int a[101]={0};
    int light,people,i,j;
    scanf("%d %d",&light,&people);

    for (i=1;i<=people;++i)
    {
        if (i==1)
        {
            for (j=1;j<=light;++j)
            {
                a[j]=1;
            }
        }
        else
        {
            for (j=1;j<=light;++j)
            {
                if ( j%i==0 && a[j]==1 ) a[j]=0;
                else if ( j%i==0 && a[j]==0 ) a[j]=1;
            }
        }
    }

    for (i=1;i<=light;++i)
    {
        if (a[i]==1) printf("%d ",i);
    }
}