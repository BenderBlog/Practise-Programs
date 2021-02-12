#include<stdio.h>
#include<string.h>

int toten (int a)
{
	int i,result=1;
	if (a==1) return 1;
	else
	{
		for (i=0;i<a-1;++i)
		{
			result *= 10;
		}
	}
	return result;
}

int main ()
{
	char a[40]={'\0'},number1[9]={'\0'},number2[9]={'\0'};
	int i,j=0,solution,situation=0,way=0,number_one=0,number_two=0,bits_one=0,bits_two=0;
	
	fgets(a,40,stdin);
	
	for (i=0; a[i]!='\n' && a[i]!='\0' ;++i)
	{
		
		if ( a[i]=='+' ||  a[i]=='-' || a[i]=='*' || a[i]=='/' || a[i]=='%' )
		{
			switch (a[i])
			{
				case '+':{way=1;break;}
				case '-':{way=2;break;}
				case '*':{way=3;break;}
				case '/':{way=4;break;}
				case '%':{way=5;break;}
				case ' ':break;
			}
			//printf("way=%d\n",way);
		}
		
		else if (a[i]==' ')
		{
			if (number1[0]=='\0') continue;
			else 
			{
				j=0;
				situation=1;
			}
		}
		
		else if (a[i]>='0' && a[i]<='9' && situation==0)
		{
			number1[j]=a[i];
			j++;
		}
		
		else if (a[i]>='0' && a[i]<='9' && situation==1)
		{
			number2[j]=a[i];
			j++;
		}
	}
	
	bits_one=strlen(number1);
	bits_two=strlen(number2);
	
	for (i=0;i<bits_one;++i)
	{
		number_one+=(number1[i]-'0')*toten(bits_one-i);
	}
	for (i=0;i<bits_two;++i)
	{
		number_two+=(number2[i]-'0')*toten(bits_two-i);
	}
	//printf("number_one=%d number_two=%d\n",number_one,number_two);
			
	switch (way)
	{
		case 1:printf("%d",number_one+number_two);break;
		case 2:printf("%d",number_one-number_two);break;
		case 3:printf("%d",number_one*number_two);break;
		case 4:printf("%d",number_one/number_two);break;
		case 5:printf("%d",number_one%number_two);break;
	}
}