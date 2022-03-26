#include<stdio.h>

int a[20][20];
int n,m,t,k;
int i,j,storage[50]={0},l,count,situation;

void process(int x)
{
    situation=0;
    for (l=0;l<50;l++) if (x==storage[l])
    {
        situation=1;
        break;
    }
    if(situation==0)
    {
        count++;
        for (l=0;l<50;l++) if (storage[l]==0) break;
        storage[l]=x;
    }
}


int main()
{
    scanf("%d %d %d %d",&n,&m,&t,&k);
    
    if ((t<=0||t>=50) || (k<0||k>t))
    {
        return 0;
    }
        
    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }

    for (i=0;i<n;i++)
    {
        for (j=0;j<m;j++)
        {
            if (a[i][j]==k)
            {
                if (a[i-1][j]!=k && i-1>=0)  process(a[i-1][j]);
                if (a[i][j-1]!=k && j-1>=0)  process(a[i][j-1]);
                if (a[i][j+1]!=k && j+1<m)   process(a[i][j+1]);
                if (a[i+1][j]!=k && i+1<n)   process(a[i+1][j]);
            }
        }
    }
    printf("%d\n",count);
}