#include <stdio.h>

int main()
{
	char compressed[50]={'\0'}, processing[50]={'\0'};
	int i = 0, j = 0, k = 0, count = 0;

	//fgets(compressed, 50, stdin);
	gets(compressed);

	for (i = 0; compressed[i] != '\n' && compressed[i] != '\0'; ++i)
	{
		
		//printf("compressed[%d] = %c\n",i,compressed[i]);
		
		if ( compressed[i] >= 'A' && compressed[i] <= 'Z' || compressed[i] >= 'a' && compressed[i] <= 'z' )
		{
			if ( compressed[i+1] >= '0' && compressed[i+1] <= '9' )
			{
				processing[j] = compressed[i];
				//printf("processing[%d] = %c\n",j,processing[j]);
				j++;				
			}
			else
			{
				printf("%c",compressed[i]);
				j=0;
			}
		}

		//printf("processing = %s\n",processing);
		
		if ( compressed[i] >= '1' && compressed[i] <= '9')
		{
			if ( compressed[i+1] >= '0' && compressed[i+1] <= '9' )
			{
				count = (compressed[i] - '0')*10 + (compressed[i+1] - '0');
			}
			else if ( compressed[i-1] >= '0' && compressed[i-1] <= '9' )
			{
				continue;
			}
			else
			{
				count = (compressed[i] - '0');
			}

			//printf("count = %d\n",count);
			
			if (count>=3)
			{
				for (k = 0; k < count; ++k)
				{
					printf("%s", processing);
				}				
			}

			j = 0;
			for (k = 0; k < 50; ++k)
			{
				processing[k] = '\0';
			}
		}
	}
}