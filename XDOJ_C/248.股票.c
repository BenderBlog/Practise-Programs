#include<stdio.h>
int main()
{
    int number,price,day,cash,stock,in_out;
    int i;

    scanf("%d %d %d",&number,&price,&day);
    stock=number*price;cash=0;

    for (i=0;i<day;++i)
    {
        scanf("%d %d",&in_out,&price);
        number+=in_out;
        stock=number*price;
        cash-=in_out*price;
    }

    printf("%d",cash+stock);
}