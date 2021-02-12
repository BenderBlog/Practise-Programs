#include<stdio.h>

int isPrime(int a)
{
	int lets_see;
	for (int i=2 ; i<a ; ++i)
	{
		lets_see = a % i;
		if (lets_see==0) return 1;
	}
	return 0;
}

int main()
{
	int number,minus;
	scanf("%d",&number);
	if (number>1 && number<1000 && number%2==0)
	{
		for (minus=2;minus<number;++minus)
		{
			int another = number - minus;
			if(isPrime(minus)==0 && isPrime(another)==0)
			{
				printf("%d %d",minus,another);
				break;
			}
		}
	}
}