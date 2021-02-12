/*
折点计数思路：每三个连续数字比大小，中间的比两头大者记为折点。
              因而，在确定输入数字个数后必须先输入两个数，方可
              再输入一个数，满足三个数连续比大小的要求。三个数
			  比较完成后，左边的作为新的中间，中间的作为新的右边。
			  如此循环n-3次即可。
*/

#include<stdio.h>
int main ()
{
	int number,left,right,center,e=0,i; 
	scanf("%d",&number);
	scanf("%d%d",&left,&center);
	for(i=3;i<=number;i++)
	{
		scanf("%d",&right);
		if( (left<center && center>right) || (left>center && center<right))	e++;
		left=center;
		center=right;
	}
	printf("%d",e);
}