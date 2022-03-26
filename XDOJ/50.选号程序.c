#include<stdio.h>
int n,m,numberone,numbertwo,i,j,k,max,temp1,temp2;
int main()
{
	scanf("%d",&n);
	scanf("%d %d ",&numberone,&numbertwo);
	if (numberone>numbertwo) max=numberone;
	else if (numberone<=numbertwo) max=numbertwo;
	if (n>2 && n<100)
	{
		for (i=2;i<n;i++)
		{
			j=0;
			k=0;
			scanf("%d",&m);
			temp1=m;
			temp2=max;
			while(temp1!=0)
			{
				j += temp1 % 10;
				temp1 /= 10;
			}
			while(temp2!=0)
			{
				k += temp2 % 10;
				temp2 = temp2 / 10;
			}
			if(j>k) max=m;
			else if(j==k)
			{
				if (m>max) max=m;
			}
		}
	}
	printf("%d",max);
}
