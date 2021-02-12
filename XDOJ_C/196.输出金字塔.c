#include<stdio.h>
char letter,i,j,k,count;
char n='A';
int l=2;
int main()
{
	scanf("%c",&letter);
	for(count='A';count<=letter;count++)
	{
		//printf("count=%c letter=%c i=%d\n",count,letter,letter-count);
		for(i=letter-count;i>=1;i--)
		{
			printf(" ");
		}
		for(j='A';j<=count;j++)
		{
			printf("%c",j);
		}
		for(k=count-1;k>='A';k--)
		{
			printf("%c",k);
		}
		printf("\n");
	}
}
