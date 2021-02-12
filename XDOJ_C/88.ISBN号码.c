#include <stdio.h>

int main()
{
	char code[14]={'\0'};
	int number=0,i=0,j=1;
	
	fgets(code,14,stdin);
	//for (i=0;i<13;++i) printf("code[%d]=%c\n",i,code[i]);
	
	for (i=0;i<12;++i) if (code[i]>='0' && code[i]<='9')
	{
		number+=(code[i]-'0')*j;
		//printf("%d*%d=%d number[%d]=%d\n",(code[i]-'0'),j,(code[i]-'0')*j,j,number);
		j++;
	}

	//printf("number=%d code[%d]=%d\n",number,12,code[12]-'0');
	number=number%11;
	//printf("number=%d code[%d]=%d\n",number,12,code[12]-'0');
	
	if ( (number == code[12]-'0') || (number == 10 && code[12] == 'X') ) printf("Right");	
	else
	{
		if (number >= 0 && number <= 9) code[12] = number + '0';
		else if (number == 10) code[12] = 'X';
		printf("%s",code);
	}
	
	return 0;
}
