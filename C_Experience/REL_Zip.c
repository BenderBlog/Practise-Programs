//2021 SuperBart@Bilibili Under The Unlicense
//程序课程作业4 REL的实现
//注意，这个方法对冗余数据很不友好，极有可能会反向优化
//强烈建议上网搜索“加强版REL算法”

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *inputFile, *outputFile;
//压缩函数
void zip()
{
	int filelen;			//每一个字符连续重复出现的次数
	char cursor,temp;		//cursor：当前读取的字符; temp: 用来判断的字符
	temp=fgetc(inputFile);	//读取第一个字符，返回读取到的字符
	filelen=1;
	while(!feof(inputFile))	//读到文件末尾时结束循环 
	{
		cursor=fgetc(inputFile);
		//若目前读取的字符和一开始的字符相同的话，重复次数加1
		if (cursor==temp){
			filelen++;
		} else {
			fputc(filelen+'0',outputFile);	//写一个字符（此处是计数数字），若失败则返回EOF 
			fputc(temp,outputFile);			//同上，此处是原字符 
			temp=cursor;					//更新判断字符的状态，重置重复字符长度
			filelen=1;
		}
	}
	//关闭文件
	fclose(inputFile);
	fclose(outputFile);		
}
//解压缩函数
void unzip()
{
	int filelen;	//重复字符长度
	char cursor;	//读取中的字符
	while(!feof(inputFile)){
		filelen = fgetc(inputFile)-'0';		//第一个字符一定是个数字，读取重复次数
		cursor = fgetc(inputFile);			//读取当前字符
		while(filelen--)					//在重复次数内，解压数据
			fputc(cursor,outputFile);
	}
	//关闭文件
	fclose(inputFile);
	fclose(outputFile);
}
int main(int argc, char* argv[]){
    if (argc == 4){
        inputFile  = fopen(argv[1], "rb");
        outputFile = fopen(argv[3], "wb");
	    if (!inputFile || !outputFile) {
		    printf("No File Detected!\n");
            return 0;
	    } else if (strcmp(argv[2],"-c") == 0){
            zip();
            printf("Zip success!\n");
            return 0;
        } else if (strcmp(argv[2],"-d") == 0){
            unzip();
            printf("Unzip success!\n");
            return 0;
        }
    } else {
        printf("No such options, read help below.\n");
        printf("'-c' zip a file with RLE.\n");
        printf("'-d' unzip a file ziped with RLE.\n");
        return 1;
    }
}
