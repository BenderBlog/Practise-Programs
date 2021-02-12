#include<stdio.h>

typedef struct information
{
    int no;
    char in[6];
    char out[6];
}input;

typedef struct summary
{
    int no;
    int total;
}all;

int timeswitch(char a[])
{
    return ((a[0]-'0')*10+(a[1]-'0'))*60+(a[3]-'0')*10+(a[4]-'0');
}

int main()
{
    int n,i,j,k;
    input a={0};
    all b[100]={0};

    scanf("%d",&n);
    for (i=0;i<n;++i)
    {
        scanf("%d %s %s",&a.no,a.in,a.out);
        for (j=0;j<n;++j)
        {
            if (b[j].no==a.no)
            {
                b[j].total+=timeswitch(a.out)-timeswitch(a.in);break;
            }
            else if (b[j].no==0)
            {
                b[j].no=a.no;
                b[j].total+=timeswitch(a.out)-timeswitch(a.in);break;
            }
        }
    }

    for (i=0;b[i].no!=0;++i)
    {
        for (j=i,k=i+1;b[k].no!=0;++k)
        {
            if (b[k].total>b[j].total) j=k;
            else if (b[k].total==b[j].total && b[k].no<b[j].no) j=k;
        }
        if (j!=i)
        {
            all temp=b[i];b[i]=b[j];b[j]=temp;
        }
    }

    for (i=0;b[i].no!=0;++i)
    {
        printf("%d %d\n",b[i].no,b[i].total);
    }
}