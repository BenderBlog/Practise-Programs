#include<stdio.h>
#include<math.h> 
int number,bits=0,max,min,a,b=1,first,second,third,i;
int main()
{
	scanf("%d",&number);
	while(1)
	{
		bits++;
		a = number / b;
		if (a<10)
		{
			printf("%d ",bits);
			break;
		}
		b = b * 10;
	}
	if (bits==1) // Super Annoying:-(
	{
		printf("%d %d",number,number);
	}
	
	else
	{
		first = number / (int)(pow(10,bits-1));
		second = (number % (int)(pow(10,bits-1))) / (int)(pow(10,bits-2));
		if (first>second)
		{
			max = first;
			min = second;
		} 
		else
		{
			max = second;
			min = first;
		}
		//printf("%d %d ",first,second);
		for(i=3;i<=bits;i++)
		{
			third = (number % (int)(pow(10,bits-i+1))) / (int)(pow(10,bits-i));
			//printf("%d\n",third);
			if (third>max) max = third;
			else if (third<min) min = third;
			first = second;
			second = third; 
		}
		printf("%d %d",max,min);
	}
} 
