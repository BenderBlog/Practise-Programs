/* Word count program written by SuperBart.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */

/* I use the KMP algorithm in this program.
 * However, you could write a simpler string match algorithm because it's more convenient.
 */

#include"KMP.h"

int main(){
    // Enter the filename.
    printf("打开文件的名称，注意要和可执行文件在同一目录下：");
    char open[256]={'\0'};
    fgets(open,256,stdin);
    open[StrLen(open)-1] = '\0';

    // Open the Files
    FILE *passage = fopen(open,"r");
    if(passage == NULL) {
      perror("文件无法打开:-(");
      return ERROR;
    }

    // Ask for the string to find.
    printf("输入需要寻找的字符串：");
    char find[30]={'\0'};
    fgets(find,30,stdin);
    find[StrLen(find)-1] = '\0';

    // 'line' refer to the line's position in the file.
    // 'gotcha' sum up to look for the total appearence.
    // string is the line which read, 1000 maxium.
    int line = 1, gotcha = 0;
    char string[1000] = {'\0'};

    // Core code, look for KMP.c
    while(fgets(string,1000,passage) != NULL){
       // Actually simple algorithm is fine.
       gotcha += StrCmp_KMP(string,find,line);
       // I believe only thinking about the first charactor is useful.
       if (find[0] >= 'a' && find[0] <= 'z'){
           find[0] = find[0] + 'A' - 'a';
       } else if (find[0] >= 'A' && find[0] <= 'Z'){
           find[0] = find[0] + 'a' - 'A';
       }
       gotcha += StrCmp_KMP(string,find,line);
       line++;
    }

    // Output total solution.
    if (gotcha == 0){
        printf("本文没有这个词:-P\n");
    } else {
        printf("%s这个词出现了%d次\n",find,gotcha);
    }

    // Close the file and goodbye.
    fclose(passage);
    return OK;
}
