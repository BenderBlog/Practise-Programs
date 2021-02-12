#include<stdio.h>
int main()
{
    char a[100]={0};
    int j=0,k=0;
    //scanf("%s",&a);     //scanf("%s",&a) == 将字符串输入到 a 数组。遇到空格之类字符就截断。                     OJ 75
    gets(a);              //这个输入字符串的方式由于易造成数组溢出，现在不再使用。                                  OJ 100
    //fgets(a,100,stdin); //从标准输入(STanDrd INput)中读取100个字符，存入数组a，多输入截取，少输入自动添加'\0'      OJ 0
    /*for (i=0;i<=100;++i)//循环输入字符串元素，输入到回车结束。                                                OJ 0
    {
        scanf("%c",&a[i]);
        if (a[i]=='\n') break;
    }*/
    while (a[j]!='\0')    //后两种方法必须用\n，否则最终结果将会多个10("\n"换行符的ASCII码是10)
    {
        k += a[j];
        printf("a[%d]=%d\n",j,a[j]);
        j++;
    }
    printf("%d",k & 0xFF);
}