#include<stdio.h>

typedef struct date
{
	int year,month,date;
}DATE;

int special_year_evaluate(int a)
{
	if ((a%4==0 && a%100!=0) || (a%400==0)) return 1;
	else return 0;
}

int main()
{
	int present=0,i;
	DATE now;
	int year[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	
	scanf("%d,%d,%d",&now.year,&now.month,&now.date);
	if (special_year_evaluate(now.year)==1) year[2]=29;
	
	for (i=0;i<now.month;++i)	present+=year[i];
	present+=now.date;
	
	printf("%d",present);
}