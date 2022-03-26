#include<stdio.h>
#include<string.h>

int main()
{
    char a[20][21]={0};
    int b[22][22]={0};  //0 nouse;1 step;2 non-step
    int n,m,c,i,j,count=0;

    scanf("%d %d %d",&n,&m,&c);
    
    for (i=0;i<=n;++i)
    {
        gets(a[i]);
        //a[i][strlen(a[i])-1]='\0';    又是一个只有gets才能过的题
    }

    
    for (i=1;i<=n;++i)
    {
        for (j=strlen(a[i]);j>0;--j)
        {
            a[i][j]=a[i][j-1];
        }
        a[i][0]='\0';
    }


    for (i=1;i<=n;++i)
    {
        for (j=1;j<=m;++j)
        {
            b[i][j]=2;
        }

    }

    i=1;j=c;b[i][j]=1;
    //printf("\nNow at a[%d][%d]=%c b[%d][%d]=%d ",i,j,a[i][j],i,j+1,b[i][j+1]);
    while(1)
    {
        switch ( a[i][j] )
        {
            case 'N':--i;break;
            case 'S':++i;break;
            case 'W':--j;break;
            case 'E':++j;break;
            default:break;
        }
        //printf("\nNow at a[%d][%d]=%c b[%d][%d]=%d ",i,j,a[i][j],i,j+1,b[i][j+1]);
        count++;
        if (b[i][j]==1)
        {
            printf("loop %d",count);
            break;
        }
        else if (b[i][j]==0)
        {
            printf("out %d",count);
            break;
        }
        else b[i][j]=1;
    }
}