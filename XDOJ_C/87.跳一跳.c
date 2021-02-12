#include<stdio.h> 
int score,situation1,situation2,i=1;
int main()
{
	scanf("%d ",&situation1);
	score = situation1;
	//printf("score = %d\n",score);
	while (1)
	{
		scanf("%d",&situation2);
		if (situation2==1)
		{
			score += situation2;
			situation1 = situation2;
			//printf("score = %d    situation1 = %d    situation2 = %d\n",score,situation1,situation2);
		}
		else if (situation2==2)
		{
			if (situation2>situation1)
			{
				i=1;
				score += situation2;
				situation1 = situation2;
				//printf("i = %d score = %d situation1 = %d    situation2 = %d\n",i,score,situation1,situation2);
			}
			else if (situation2 = situation1)
			{
				i++;
				score += situation2 * i;
				situation1 = situation2;
				//printf("i = %d score = %d situation1 = %d    situation2 = %d\n",i,score,situation1,situation2);
			}
		}
		else if (situation2==0)
		{
			printf("%d",score);
			break;
		}
	}
} 
