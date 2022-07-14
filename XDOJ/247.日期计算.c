#include<stdio.h>

int main ()
{
    int y,d,m=1;
    int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    scanf("%d%d",&y,&d);
    
    if (( y%4==0 && y%100!=0 ) || ( y%400==0 ))  month[2]=29;
    while (d-month[m]>0)
    {
        d-=month[m];
        m++;
    }

    printf("%d %d\n",m,d);
}