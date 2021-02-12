#include <stdio.h>

int main()
{
	char string[50]={'\0'}, buffer[25]={'\0'};
	int i,j=0,k,situation=0;
	
	fgets(string,50,stdin);
	
	for (i=0; string[i]!='\n' && string[i]!='\0' ;++i)
	{
		//printf("string[%d]=%c\n",i,string[i]);
		
		if ( string[i]=='(' || string[i]=='[' || string[i]=='{' )
		{
			buffer[j]=string[i];
			//printf("	buffer[%d]=%c\n",j,buffer[j]);
			j++;
		}
		
		//printf("i=%d buffer is %s\n",i,buffer);
		
		if ( string[i]==')' || string[i]==']' || string[i]=='}' )
		{
			for (k=0;k<25;++k)
			{
				//printf("	buffer[%d]=%c string[%d]=%c buffer[k]-string[i]=%d\n",k,buffer[k],i,string[i],buffer[k]-string[i]);
				if ( buffer[k]-string[i]==-1 && string[i]==')' || buffer[k]-string[i]==-2 )
				{
					buffer[k]='\0';
					//printf("		now buffer[%d]=%c\n",k,buffer[k]);
					break;
				}
			}
		}
		
	}
	
	for (i=0;i<25;++i)
	{
		if (buffer[i]!='\0')
		{
			printf("no");
			situation=1;
			break;
		}
	}
	if (situation==0) printf("yes");

	return 0;
}
