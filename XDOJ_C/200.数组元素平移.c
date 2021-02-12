#include <stdio.h>
int main() 
{
	int a[10]={1,2,3,4,5,6,7,8,9,10},b[10]={0};
	int p,i,end;
	scanf("%d",&p);
	for (i=0;i<10;++i)
	{
		if (i+p+1<10)
		{
			b[i] = a[i+p+1];
			printf("%d ",b[i]);
		}
		else if (i+p+1>=10)
		{
			end=i;
			b[i] = a[(i+p+1)%10];
			printf("%d ",b[i]);
		}
	}
}
