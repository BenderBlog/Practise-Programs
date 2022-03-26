#include <stdio.h>
int number, fib1 = 1, fib2 = 1, fib3, d, e, f;

int fib()
{
	for (d = 3; d <= number; d++)
	{
		fib3 = fib1 + fib2;
		fib1 = fib2;
		fib2 = fib3;
	}
	return fib3;
}

int evaluate()
{
	for (e = 2; e < fib3; e++)
	{
		if (fib3 % e == 0)
		{
			f = 1;
			break;
		}	
	}
}

int main()
{
	scanf("%d", &number);
	if (number > 1 && number <= 40)
	{
		fib(number);
		evaluate(fib3);
		if (f == 1)  printf("%d", fib3);
		else printf("yes");
	}
}
