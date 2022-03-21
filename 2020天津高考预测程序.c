#include <stdio.h>
int position,subject;
double guess;

int lecture()
{
	printf("你在大学一定会收获爱情的:-)\n");
	printf("再确认一遍，你选的是偏文科目，名次为%d。\n",position);
	guess = position * 1 / 4;
	printf("你今年可以参照去年的%0.1f的文科位次来报志愿。",guess);
	return 0;
}

int physics()
{
	printf("小心秃头:-)\n");
	printf("再确认一遍，你选的是偏理科目，名次为%d。\n",position);
	guess = position * 3 / 4;
	printf("你今年可以参照去年的%0.1f的理科位次来报志愿。",guess);
	return 0;
}

int garbage()
{
	printf("What's up doc?\n");
	printf("再确认一遍，你选的名次为%d。\n",position);
	return 0;
}

int main()
{
	printf("请输入你的名次：");
	scanf("%d",&position);
	printf("你今年学科状况如何？偏文请按1，偏理请按2：");
	scanf("%d",&subject);
	if (subject==1) lecture(position);
	else if (subject==2) physics(position);
	else garbage(position);
}

