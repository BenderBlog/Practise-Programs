#include<stdio.h>
#include<string.h>

int main ()
{
    char string[100]={'\0'},word[9]={'\0'},box[100][9]={'\0'};
    int times=0;
    int i,j=0,k=0,situation=0;

    fgets(string,100,stdin);
    fgets(word,8,stdin);
    string[strlen(string)-1]='\0';
    word[strlen(word)-1]='\0';
    //gets(string);             不用gets过不了，原因不明
    //gets(word);
    

    for (i=0;i<strlen(string);++i)
    {
        //printf("Eval string[%d]=%c ",i,string[i]);
        if (string[i]==' ' && string[i+1]!=' ')
        {
            //printf("1, j=%d, k=%d\n",j,k);
            j++;k=0;
        }
        else if (string[i]==' ' && string[i+1]==' ')
        {
            //printf("2, j=%d, k=%d\n",j,k);
            k=0;continue;
        }
        else
        {
            box[j][k]=string[i];
            //printf("3, j=%d, k=%d, box[%d][%d]=%c\n",j,k,j,k,box[j][k]);
            ++k;
        }
    }
    /*
    for (i=0;box[i][0]!='\0';++i)
    {
        printf("box[%d]=%s\n",i,box[i]);
    }
    */
    if (box[0][0]=='\0') situation=1;
    else if (box[0][0]!='\0') situation=0;

    for (i=situation;box[i][0]!='\0';++i)
    {
        //printf("Eval box[%d]=%s\n",i,box[i]);
        if(strcmp(word,box[i])==0)
        {
            times++;
            //printf("Correct! Now time is %d\n",times);
        }            
    }
    printf("%s %d",word,times);
    return 0;
}