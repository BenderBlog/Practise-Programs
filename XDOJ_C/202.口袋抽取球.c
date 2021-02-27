#include<stdio.h>
int main()
{
	int red,white,black;
	for(red=0;red<=3;red++)
		for(white=0;white<=4;white++)
			for(black=0;black<=5;black++)
				if(red+white+black==8) 
					printf("%d %d %d\n",red,white,black);
}
