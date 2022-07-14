#include<stdio.h>
int main()
{
	int a,b,c,n;
	scanf("%d",&n);
	if (n>1000 && n<2000)
	{
		for (a=0;a<10;a++) 
			for (b=0;b<10;b++)
				for (c=0;c<10;c++)
			if (n == (a+c)*101 + b*20)printf("%d %d %d\n",a,b,c); 
	}
}
