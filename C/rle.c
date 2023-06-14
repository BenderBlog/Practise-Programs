#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//压缩函数
void zip(FILE* inputFile,FILE* outputFile)
{
	int len;			    //字符连续重复次数
	char cursor,temp;		//储存当前指针所指字符和上一个字符
	temp=fgetc(inputFile);
	len=1;
    char len_s[1000] = "";
	while(!feof(inputFile))
	{
		cursor=fgetc(inputFile);
		if (cursor==temp){//遇到相同字符，重复次数+1
			len++;
		} else { //遇到不同的字符，则进行写入操作，并重置状态
            itoa(len,len_s,10); //按10进制，转化整数为字符串
			fputs(len_s,outputFile);	    //写入重复的次数(已转化为字符)
			fputc(temp,outputFile);			//写入需要重复的字符内容
            //重置计数状态
			temp=cursor;
			len=1;
		}
	}
	fclose(inputFile);
	fclose(outputFile);
}

//解压缩函数
void unzip(FILE* inputFile,FILE* outputFile)
{
	int length;//重复字符长度
	char cur;	//读取中的字符
    while(fscanf(inputFile,"%d%c",&length,&cur) != EOF){
        while(length--)
            fputc(cur,outputFile);
    }
	fclose(inputFile);
	fclose(outputFile);
}

int main(int argc, char* argv[]){
    if (argc == 4){
        FILE *input, *output;
        input  = fopen(argv[1], "rb"); //打开可读文件
        output = fopen(argv[3], "wb"); //打开可写文件
	    if (!input || !output) { //缺少部分文件
		    printf("File Not Found.\n");
            return 0;
	    } else if (strcmp(argv[2],"-c") == 0){ //进行压缩操作
            zip(input,output);
            printf("Zip Finished.\n");
            return 0;
        } else if (strcmp(argv[2],"-d") == 0){ //进行解压操作
            unzip(input,output);
            printf("Unzip Finished.\n");
            return 0;
        }
    } else { //参数数量匹配不上
        printf("'-c' zip a file\n");
        printf("'-d' unzip a file\n");
        return 1;
    }
}
