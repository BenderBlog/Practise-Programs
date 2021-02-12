#include <stdio.h>
int main ()
{
	double f;
	double c;
	scanf("%lf",&f);
	c = (f - 32) * 5 / 9;
	printf("%.2f",c);
	return 0;
}
