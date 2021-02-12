#include<stdio.h>
int main()
{
	int n,time=0;
	scanf("%d",&n);
	if (n>1 && n<100000)
	{
		while(n!=1)
		{
			if (n%2!=0) 
			{
				n=3*n+1;
				time++;
			}
			else if(n%2==0)
			{
				n=n/2;
				time++;
			} 
		}
		printf("%d",time);
	}
}
