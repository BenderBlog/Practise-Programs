#include <stdio.h>

int power(int a,int b)
{
	int i,result=1;
	for (i=1;i<=b;++i)
	{
		result *= a;
	}
	return result;
}

int main() 
{
	int number,a[9]={0},add=0,nozero=0,i,j,situation=1;
	scanf("%d",&number);
	for (i = 8; i >= 0; --i) 
	{
		a[i] = number/power(10,i);
		number = number%power(10,i);
	}
	for (i = 8; i >= 0; --i) 
	{
		if (a[i]!=0)
		{
			nozero = i;
			break;
		}
	}
	for (i=0,j=nozero;i<=nozero,j>=0;++i,--j)
	{
		if (a[i]!=a[j]) 
		{
			situation=0;
			printf("no");
			break;
		}
		else
		{
			add += a[i];
		}

	}
	if (situation==1)
	{
		printf("%d",add);
	}

}