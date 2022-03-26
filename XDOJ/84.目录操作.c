#include <stdio.h>
#include <string.h>

char location[200]={'\0'},situation=0;

void cd (char a[], int i, int up)
{
	int d=strlen(location),j=0;
	if (a[0]=='/')
	{
		for (j=0;j<d;++j) location[j]='\0';
		strcpy(location,a);
	}
	else if ( up==1 && ( a[0]!='/' || (a[0]=='/' && a[1]!='\n') ) )
	{
		for (j=d-1;location[j]!='/';--j) location[j]='\0';
		if (j!=0) location[j]='\0';
	}
	else if ((a[0]>='a' && a[0]<='z') || (a[0]>='0' && a[0]<='9') )
	{
		if (d==1)
		{
			for (j=0;a[j]!='\0';++j)
			{
				location[d]=a[j];++d;
			}
		}
		else
		{
			location[d]='/';
			for (j=0;a[j]!='\0';++j)
			{
				++d;
				location[d]=a[j];
			}
		}
		
	}
}

void eval (char a[])
{
	int i=0,j=0,up=0;
	char option[200]={'\0'};
	
	if ( a[0]=='p' && a[1]=='w' && a[2]=='d' )
	{
		printf("%s\n",location);
		situation=1;
	}
	else if ( a[0]=='c' && a[1]=='d' )
	{
		if ( a[3]=='.' && a[4]=='.' )
		{
			up=1;
		}	
		else
		{
			for (i=3;a[i]!='\0';++i)
			{
				if ( a[i]=='\0' )
					break;
			
				else if ( a[i]=='/' || (a[i]>='a' && a[i]<='z') || (a[i]>='0' && a[i]<='9') )
				{
					option[j] = a[i];
					++j;
				}
			}
		}
		cd(option,strlen(option),up);
	}	
}

int main ()
{
	fgets(location,200,stdin);
	int i=0;
	while (++i)
	{
		if (location[i]=='\n')
		{
			location[i]='\0';break;
		}
	}	
	while (1)
	{
		char command[200]={'\0'};
		fgets(command,200,stdin);
		eval(command);
		if (situation==1) break;	
	}
}