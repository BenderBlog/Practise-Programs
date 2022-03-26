#include<stdio.h>

int main()
{
    int force[100][100]={0};
    int m,n,i=0,j=0,max=0,bigstart=0,bigend=0;
    int temp=0,temp1=0,temp2=0;

    scanf("%d %d",&m,&n);
    for (i=0;i<m;++i)
    {
        for (j=0;j<n;++j)
        {
            scanf("%d",&force[i][j]);
        }
    }

    for (i=0;i<m;i++)
    {
        //printf("The %dth line\n",i+1);
        temp=0;temp1=0;temp2=0;
        bigstart=0;bigend=0;
        max=0;

        for (j=0;j<n;j++)
        {
            //printf("Evaluating a[%d][%d]=%d\n",i,j,force[i][j]);

            if ((j!=0 && force[i][j]==1 && force[i][j-1]==0) || (j==0 && force[i][j]==1))
            {
                //printf("    1 started at a[%d][%d]=%d\n",i,j,force[i][j]);
                temp1=j;
            }

            if ((j!=n-1 && force[i][j]==1 && force[i][j+1]==0) || (j==n-1 && force[i][j]==1))
            {
                //printf("    1 ended at a[%d][%d]=%d\n",i,j,force[i][j]);
                temp2=j;
            }
            //printf("        temp1=%d temp2=%d temp=%d\n",temp1,temp2,temp);
            if ( temp2!=0 )
            {
                temp = temp2 - temp1;
                if (temp>=max)
                {                    
                    //printf("        This solution is bigger than max=%d so far\n",max);
                    
                    max=temp;
                    bigstart = temp1;
                    bigend = temp2;
                    
                    //printf("        Now max=%d bigstart=%d bigend=%d\n",max,bigstart,bigend);
                }
            }
        }
        //printf("Now bigstart=%d bigend=%d\n",bigstart,bigend);
        if (bigend!=0) printf("%d %d\n",bigstart,bigend);
        else if (force[i][0]==1 && temp1==0 && temp2==0) printf("0 0\n");
        else printf("-1 -1\n");
    }
}