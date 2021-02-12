#include<stdio.h>
#include<math.h>
int main()
{
	int n,i;
	double passway=100,height;
	scanf("%d",&n);
	if (n>=5 && n<=15)
	{
		for(i=2;i<=n;i++)
		{
			passway=passway+100.0*pow(0.5,i-2);
			height=100.0/pow(2.0,i);
		}
		printf("S=%.3f h=%.3f",passway,height); 
	}
}
