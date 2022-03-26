#include<stdio.h>
int main()
{
	int i,number=0;
	for (i=100;i<500;i++)
	{
		if ( (i%11==0 || i%7==0) && (i%77!=0)) number++;
	}
	printf("%d",number);
	return 0;
}
