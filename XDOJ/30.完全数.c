#include<stdio.h>
int main()
{
	int left,right,wanquanshu,a,b;
	b=1;
	scanf("%d %d",&left,&right); //输入整数范围[left，right]
        if(left==1) 
    {
        left=left+1;
    }          
	for(wanquanshu=left;wanquanshu<=right;wanquanshu++)     //在整数范围[left,right]内一个数一个数筛选，每个数为完全数（wanquanshu）
	{
		a=wanquanshu;										//a赋上完全数（wanquanshu）的值
		for(b=1;b<=a;b++)  if(wanquanshu%b==0) a=a-b;		//b从1一直
		if (a==0) printf("%d\n",wanquanshu);
	}
	return 0;
}
