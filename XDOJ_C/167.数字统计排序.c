#include<stdio.h>

int main()
{
    int n;
    int box[200][2]={0};
    int i,j,k;

    scanf("%d",&n);
    for (i=0;i<n;++i)
    {
        scanf("%d",&box[i][0]);
        box[i][1]=1;
    }

    for (i=0;i<n;++i)
    {
        for (j=i+1;j<n;++j)
        {
            if (box[j][0]==box[i][0])
            {
                box[j][0]=-1;
                box[i][1]++;
            }
        }
        if (box[i][0]==-1) box[i][1]=0;
    }

    for (i=0;i<n;++i)
    {
        for(j=i,k=i+1;k<n;++k)
        {
            if (box[k][1]>box[j][1]) j=k;
            else if ( box[k][1]==box[j][1] && box[k][0]<box[j][0] ) j=k;
        }
        if (j!=i)
        {
            int temp;
            temp=box[i][0];box[i][0]=box[j][0];box[j][0]=temp;
            temp=box[i][1];box[i][1]=box[j][1];box[j][1]=temp;
        }
    }
    printf("\n");
    for (i=0;i<n;++i)
    {
        if (box[i][0]!=-1)
            printf("%d %d\n",box[i][0],box[i][1]);
    }
}