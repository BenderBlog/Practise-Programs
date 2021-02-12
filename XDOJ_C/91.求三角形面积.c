#include<stdio.h>
#include<math.h>
int main ()
{
	double a,b,c,d,e;
	scanf("%lf %lf %lf",&a,&b,&c);
	e = (a+b+c) / 2.0;
	d = sqrt(e*(e-a)*(e-b)*(e-c));
	printf("%.2f",d);
}
