#include <stdio.h>

int main() {
	int m, i,j,a[20][20]={0},max[42]={0};
	scanf("%d", &m);
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < m; ++j)
		{
			if (j == m)break;
			scanf("%d", &a[i][j]);
		}
	}

	for (i = 0; i < m; ++i) 
	{
		for (j = 0; j < m; ++j) 
		{
			max[i] += a[i][j];
			//printf("a[%d][%d]=%d  corrent max[%d]=%d\n",i,j,a[i][j],i,max[i]);
		}
	}
	
	for (i = m; i < 2 * m; ++i) 
	{
		for (j = 0; j < m; ++j) 
		{
			max[i] += a[j][i-m];
			//printf("a[%d][%d]=%d  corrent max[%d]=%d\n",i-m,j,a[i-m][j],i,max[i]);
		}
	}

	for (i = 0; i < m; ++i) 
	{
		max[2*m] += a[i][i];
		max[2*m+1] += a[i][m-1-i];
		//printf("a[%d][%d]=%d  a[%d][%d]=%d max[%d]=%d max[%d]=%d\n",i,i,a[i][i],i,m-1-i,a[i][m-1-i],2*m,max[2*m],2*m+1,max[2*m+1]);
	}

	for (i=0; i<2*m+2; ++i)
	{
		int j,k;
		for (j=i+1,k=i;j<2*m+2;++j)
		{
			if (max[j]>max[k]) 
			{
				k=j;
			}

		}
		if (k!=i)
		{
			int t;
			t=max[i]; max[i]=max[k]; max[k]=t;
		}
	}
	
	for (i=0; i<2*m+2; ++i) printf("%d ",max[i]);

	return 0;	
}