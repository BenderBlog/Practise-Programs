#include<stdio.h>
int n,i,j,Multi=1,AddOfMulti;
int main()
{
	scanf("%d",&n);
	if (n>=1 && n<=10);
	{
		for (i=1;i<=n;i++)
		{
			Multi *= i;
			for (j=1;j<=1;j++)
			{
				AddOfMulti += Multi;
			}
		}
	}
	printf("%d %d %d",n,Multi,AddOfMulti);
}
