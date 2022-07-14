#include<stdio.h>
int main()
{
	double ferou = 7.86;
	double aurou = 19.3;
	double PI = 3.1415926;
	int fezhijing;
	int auzhijing;
	double fegram;
	double augram;
	scanf("%d %d",&fezhijing,&auzhijing);
	fegram = (4.0 / 3.0) * (fezhijing / 20.0) * (fezhijing / 20.0) * (fezhijing / 20.0) * PI * ferou;
	augram = (4.0 / 3.0) * (auzhijing / 20.0) * (auzhijing / 20.0) * (auzhijing / 20.0) * PI * aurou;
	printf("%.3f %.3f",fegram,augram);
}
