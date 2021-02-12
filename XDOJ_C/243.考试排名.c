#include<stdio.h>

typedef struct student
{
    char name[20];
    int first;
    int second;
    int third;
    int forth;
    int fifth;
    int add;
    int total;
}STUDENT;

int main ()
{
    int person,i,j,k;
    STUDENT a[100],temp;

    scanf("%d",&person);
    for (i=0;i<person;++i)
    {
        //printf("i=%d\n",i);
        scanf("%s %d %d %d %d %d %d",a[i].name,&a[i].first,&a[i].second,&a[i].third,&a[i].forth,&a[i].fifth,&a[i].add);
        a[i].total=a[i].first+a[i].second+a[i].third+a[i].forth+a[i].fifth+a[i].add;
    }
    /*
    printf("\n");
    for (i=0;i<person;++i)
    {
        printf("%s %d %d\n",a[i].name,a[i].total,a[i].add);
    }
    */
    for (i=0;i<person;++i)
    {
        for (j=i,k=i+1;k<person;++k)
        {
            if (a[k].total>a[j].total)  j=k;
            else if (a[k].total==a[j].total && a[k].add>a[j].add)  j=k;
        }
        if (j!=i)
        {
            temp=a[i];a[i]=a[j];a[j]=temp;
        }
    }

    printf("\n");
    for (i=0;i<person;++i)
    {
        printf("%s %d %d\n",a[i].name,a[i].total,a[i].add);
    }
}