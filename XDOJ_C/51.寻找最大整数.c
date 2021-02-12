#include<stdio.h>

int main()
{
	int a,b,c,d,e,f,g;
	scanf("%d %d %d %d",&a,&b,&c,&d);
	if (a>b) e=a;
	else e=b;
	if (c>d) f=c;
	else f=d;
	if (e>f) g=e;
	else g=f;
	printf("%d",g);
}
