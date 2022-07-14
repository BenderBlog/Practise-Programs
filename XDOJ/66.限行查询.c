#include<stdio.h>
int day,level,number,lastnumber;

int evaluatenormal()
{
	switch(day)
	{
		case 1 : {if (lastnumber == 1 || lastnumber == 6) printf ("yes");else printf("no");break;}
		case 2 : {if (lastnumber == 2 || lastnumber == 7) printf ("yes");else printf("no");break;}
		case 3 : {if (lastnumber == 3 || lastnumber == 8) printf ("yes");else printf("no");break;}
		case 4 : {if (lastnumber == 4 || lastnumber == 9) printf ("yes");else printf("no");break;}
		case 5 : {if (lastnumber == 5 || lastnumber == 0) printf ("yes");else printf("no");break;}
	}
	return 0;
}

int evaluatealert()
{
	if (day%2==1 && lastnumber%2==1) printf ("yes");
	else if (day%2==0 && lastnumber%2==0) printf ("yes");
	else printf("no");
	return 0;
}
int evaluatelevel()
{
	if (level < 200) printf("no");
	else if (level >= 200 && level < 400) evaluatenormal(day,lastnumber);
	else if (level >= 400) evaluatealert(day,lastnumber);
	return 0;
}

int main()
{
	scanf("%d %d %d",&day,&level,&number);
	lastnumber = number % 100000 % 10000 % 1000 % 100 % 10;
	printf("%d\n",lastnumber);
	if ( day == 6 || day == 7 ) printf("no");
	else evaluatelevel(level,day,lastnumber);
}
