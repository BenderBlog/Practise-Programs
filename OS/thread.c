#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	// For sleep().

// Critical region, because both threads needs to access this.
int a;
// Lock Variable
int turn = 0;

// Thread 2.
void * th(void *p)
{
	while(1)
	{	
		while(turn!=1) 			/*loop*/;
		sleep(1);a=0;			// Access Critical Region
		printf("a=%d haha\n",a);// Stop access.
		turn=0;					// Change mark.
	}
}

int main()
{
	a=0;
	pthread_t myth;
	pthread_create(&myth,NULL,th,NULL);

	// Thread 1.
	while(1)
	{
		while(turn!=0)			/*loop*/;
		sleep(1);a=1;			// Access Critical Region.
		printf("a=%d hehe\n",a);// Stop access.
		turn=1;					// Change mark.
		
	}
}

