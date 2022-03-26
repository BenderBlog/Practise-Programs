#include<stdio.h>
double fib(int a)
{
	if ( a==1 || a==2 ) return 1;
	else return fib(a-1)+fib (a-2);
}

int main()
{
	int i,n;
	double a,sum=0;
	scanf("%d",&n);
	if (n>=2 && n<=30)
	{
		for (i=1;i<=n;++i)
		{
			a = fib(i+2) / fib(i+1);
			sum += a;
		}
		printf("%0.2f",sum);
	}

}