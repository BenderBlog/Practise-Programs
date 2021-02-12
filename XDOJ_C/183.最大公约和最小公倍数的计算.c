#include<stdio.h>
int main()
{
	int m,n,a,b,c,d,max,min;
	scanf("%d %d",&m,&n);
	if (m<n) 
	{
		max=n;
		min=m;
	}
	else
	{
		max=m;
		min=n;
	}
	for (a=min;a>0;a--)
	{
		b = m % a;
		c = n % a;
		if (b == 0 && c == 0) 
			{
				d = m * n / a;
				printf("%d %d",a,d);				
				break; 
			}
	}
} 
