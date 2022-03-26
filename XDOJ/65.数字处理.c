#include<stdio.h>
#include<math.h>
int number;

int cooking()
{
	int a,b=0;
	while(number!=0)
	{
		a = number % 10;
		//printf("a=%d ",a);
		b = b + a;
		//printf("b=%d ",b);
		number = number / 10;
		//printf("number=%d\n",number);
	}
	number = b;
	return number;
}

int main()
{
	scanf("%d",&number);
	while (number>=10)	
	{
		cooking(number);
	} 
	printf("%d",number);
}
