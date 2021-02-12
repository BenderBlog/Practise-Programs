#include<stdio.h>
int main()
{
	int person=0,situation,tickets[100]={0};
	int train[20][5]={0};
	int i,j,k,count,start;

	scanf("%d",&person);
	for (i=0;i<person;++i)
	{
		scanf("%d",&tickets[i]);
	}

	for (k=0;k<person;++k)
	{
		situation=0;
		for (i=0;i<20;++i)
		{
			start=-1;count=0;
			for (j=0;j<5;++j)
			{
				if (train[i][j]==0)
				{
					if ( train[i][j-1]!=0 || j==0 ) start=j;
					count++;
				}
			}

			if ( start==-1 || tickets[k] > count ) continue;
			else if ( tickets[k] <= count )
			{
				for (j=start;j<start+tickets[k];++j)
				{
					train[i][j]=k+1;
					printf("%d ",i*5+j+1);
				}
				situation=1;
				printf("\n");
				break;
			}
		}
		
		if (situation==1) continue;
		else if (situation==0)
		{
			for (i=0;i<20;++i)
			{
				for (j=0;j<5;++j)
				{
					if (train[i][j]==0)
					{
						train[i][j]=k+1;
						printf("%d ",i*5+j+1);
					}
				}
			}
			printf("\n");
			break;
		}
	}
}