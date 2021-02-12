#include<stdio.h>
#include<string.h>

/*
    strlen@string 是用来判断字符串长度的函数
*/

int main()
{
    char passwd[51];
    int i=0,score=0,eval[4]={0,0,0,0};
    
    gets(passwd);
    
    if (strlen(passwd)!=0) score=1;
    else score=0;
    //printf("Basic number is %d\n",score);
    
    if (strlen(passwd)>8) score+=1;
    //printf("Added advanced number is %d\n",score);

    if (score!=0)
    {
        score=score-1;
        for (i=0;i<strlen(passwd);++i)
        {
            if (passwd[i]>='A' && passwd[i]<='Z') ++eval[0];
            else if (passwd[i]>='a' && passwd[i]<='z') ++eval[1];
            else if (passwd[i]>='0' && passwd[i]<='9') ++eval[2];
            else ++eval[3];
        }
        //printf("Upper=%d Lower=%d Number=%d Others=%d\n",eval[0],eval[1],eval[2],eval[3]);
        for (i=0;i<4;++i)
        {
            if (eval[i]!=0) ++score;
            //printf("Added advanced number is %d\n",score);
        }
    }
    printf("%d",score);
}