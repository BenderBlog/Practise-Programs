#include<stdio.h>
int main()
{
    int a[100][100],m,n;
    int i,j,k,line,row,min,situation,count=0;
    scanf("%d %d",&m,&n);
    for (i=0;i<m;++i)
    {
        for (j=0;j<n;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for (i=0;i<m;++i)
    {
        situation=0;
        min=a[i][0];
        for (j=1;j<n;++j)
        {
            if ( a[i][j]<min )
            {
                min=a[i][j];line=i;row=j;
            }
        }
        for (k=0;k<m;++k)
        {
            if (a[k][row]>a[line][row])
            {
                situation=1;
                break;
            }
        }
        if (situation==0)
        {
            printf("%d %d %d\n",line,row,a[line][row]);
            ++count;
        }
    }
    if (count==0)
    {
        printf("no\n");
    }
}