#include<stdio.h>
#include<math.h>
int function(int a,int b)
{
	int i,k,temp1,temp2,number=0,bits=0,l=0;
	for (i=a;i<=b;i++)
	{
		temp1 = i;
		temp2 = i;
		k = 0;
		bits = 0;
		while (temp1!=0)
		{
			temp1 /= 10;
			bits++;
		}
		if (bits<=2) 
		{
			continue;
		}
		while(temp2!=0)
		{
			l=temp2%10;
			k+=pow(l,bits);
			temp2=temp2/10;
		}
		if (k==i)
		{
			number++;
		} 
	}
	return number;
}
int main()
{
	int a,b,left,right;
	scanf("%d%d",&a,&b);
	left = a > b ? b : a;
	right = a > b ? a : b;
	printf("%d",function(left,right));
}