#include<stdio.h>

typedef struct STUDENT
{
    int number;
    char name[11];
    double a,b,c;
    double avg;
} student;

int main()
{
    int n,i,j,k;
    student a[100];

    scanf("%d",&n);
    for (i=0;i<n;++i)
    {
        scanf("%d %s %lf %lf %lf",&a[i].number,a[i].name,&a[i].a,&a[i].b,&a[i].c);
        a[i].avg=(a[i].a+a[i].b+a[i].c)/3;
    }

    for (i=0;i<n;++i)
    {
        for (j=i,k=i+1;k<n;++k)
        {
            if (a[k].avg>a[j].avg) j=k;
        }
        if (j!=i)
        {
            student temp=a[j];a[j]=a[i];a[i]=temp;
        }
    }

    printf("\n");
    for (i=0;i<n;++i)
    {
        printf("%d %s %.1f\n",a[i].number,a[i].name,a[i].avg);
    }

}