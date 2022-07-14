#include<stdio.h>

struct student
{
    char id[20];
    int score_of_all;
    int score_of_english;
}xuesheng[200],temporary;

int main()
{
    int total,passed,i,j,k;
    
    scanf("%d %d",&total,&passed);
    for (i=0;i<total;++i)
    {
        scanf("%s %d %d", xuesheng[i].id, &xuesheng[i].score_of_all , &xuesheng[i].score_of_english );
    }

    for (i=0;i<total;++i)
    {
        for (j=i,k=i+1;k<total;++k)
        {
            if (xuesheng[k].score_of_all > xuesheng[j].score_of_all)
            {
                j=k;
            }
            else if (xuesheng[k].score_of_all == xuesheng[j].score_of_all)
            {
                if (xuesheng[k].score_of_english > xuesheng[j].score_of_english)
                {
                    j=k;
                }
            } 
 
        }
        if (j!=i)
        {
           temporary=xuesheng[i];xuesheng[i]=xuesheng[j];xuesheng[j]=temporary;
        }
    }

    printf("\n");

    for (i=0;i<passed;++i)
    {
        printf("%s %d %d\n", xuesheng[i].id, xuesheng[i].score_of_all , xuesheng[i].score_of_english );
        //printf("%d\n",xuesheng[i].score_of_all);
    }
}