#include<stdio.h>

typedef struct a
{
    int number;
    int startx,starty;
    int endx,endy;
}windows;

int main()
{
    windows a[10];
    int n,m,i,j=1,clickx,clicky;
    scanf("%d %d",&n,&m);
    for (i=n-1;i>=0;--i)
    {
        a[i].number=j;j++;
        scanf("%d %d %d %d",&a[i].startx,&a[i].starty,&a[i].endx,&a[i].endy);
    }
    for (i=0;i<m;++i)
    {
        int situation=0;
        scanf("%d %d",&clickx,&clicky);
        for (j=0;j<n;++j)
        {
            if (clickx>=a[j].startx && clickx<=a[j].endx)
            {
                if (clicky>=a[j].starty && clicky<=a[j].endy)
                {
                    windows temp=a[0];a[0]=a[j];a[j]=temp;
                    printf("%d\n",a[0].number);
                    situation=1;break;
                }
            }
        }
        if (situation==0) printf("IGNORED\n");
    }
}