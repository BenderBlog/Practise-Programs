//2021 SuperBart@Bilibili Under The Unlicense
//程序课程作业3 图像缩放
//魔改自  https://blog.csdn.net/zimuzi2019/article/details/106721230
//BMP解释 https://blog.csdn.net/Louis_815/article/details/53783497
//		 https://en.jinzhao.wiki/wiki/BMP_file_format

#include <stdio.h>
#include <stdlib.h>	//atof,atoi,malloc
#pragma pack(1)     //对齐内存

//文件信息头结构体
typedef struct tag_BITMAP_FILE_HEADER {
	unsigned short bitmapType;      // 必须是BM字符串，对应的十进制19778，否则不是bmp格式文件
	unsigned int bitmapSize;        // 文件大小 以字节为单位(2-5字节)
	unsigned short bitmapReserved1; // 保留，必须设置为0 (6-7字节)
	unsigned short bitmapReserved2; // 保留，必须设置为0 (8-9字节)
	unsigned int bitmapOffsets;     // 从文件头到像素数据的偏移  (10-13字节)
} BITMAPFILEHEADER;

//图像信息头结构体
typedef struct tag_BITMAP_INFO_HEADER {
	unsigned int bitmapSize;         // 此结构体的大小(14-17字节)
	long bitmapWidth;                // 图像的宽  (18-21字节)
	long bitmapHeight;               // 图像的高  (22-25字节)
	unsigned short	bitmapPlate;     // 表示bmp图片的平面属，显然显示器只有一个平面，所以恒等于1 (26-27字节)
	unsigned short bitmapBitCount;   // 一像素所占的位数，一般为24   (28-29字节)
	unsigned int bitCompression;     // 说明图象数据压缩的类型，0为不压缩?(30-33字节)
	unsigned int bitSizeImage;       // 像素数据所占大小 这个值应该等于上面文件头结构中bfSize-bfOffBits (34-37字节)
	long bitXPelsPerMeter;           // 说明水平分辨率，用像素米表示。一般为0 (38-41字节)
	long bitYPelsPerMeter;           // 说明垂直分辨率，用像素米表示。一般为0 (42-45字节)
	unsigned int bitColourUsed;      // 说明位图实际使用的彩色表中的颜色索引数（设为0的话，则说明使用所有调色板项） (46-49字节)
	unsigned int bitColourImportant; // 说明对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要(50-53字节)
} BITMAPINFOHEADER;

//调色板信息，鉴于我们早已进入真彩色时代，就不考虑了

//文件头
BITMAPFILEHEADER inputFileHeader;
BITMAPFILEHEADER outputFileHeader;
//图像信息
BITMAPINFOHEADER inputInfoHeader;
BITMAPINFOHEADER outputInfoHeader;
//图像每行需要占用多少字节呢？
long inputLineByteSize;
long outputLineByteSize;
//储存目标文件的所有像素点数据
unsigned char *inputData;
unsigned char *outputData;
//加载图像
void LoadBmp(const char *bmpName) {
	
	FILE *fp = fopen(bmpName, "rb");
	if (fp == 0) {
		printf("Open Failed\n");
		return;
	}
	//如果文件样式不满足要求，直接退出
	fseek(fp, 0, 0);
	fread(&inputFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	if (inputFileHeader.bitmapType != 19778) {
		printf("Not a legal pic file:-(\n");
		return;
	}
	//读取图像信息，并根据文件头文件里图像大小信息和偏移信息
	//(图像文件头信息，图片信息和调色板)来得出数据区大小
	//貌似一次read之后内存指针会移动的，所以我们可以不用fseek来强制改变内存指针指向了
	//fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	fread(&inputInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	inputData = (unsigned char *)malloc(inputFileHeader.bitmapSize - inputFileHeader.bitmapOffsets);
	fread(inputData, inputFileHeader.bitmapSize - inputFileHeader.bitmapOffsets, 1, fp);
}

//存储函数
void SaveBmp(char *output) {
	//读取(新建)输出文件
	FILE *file = fopen(output, "wb");
	if (file == 0) {
		return;
	}
	//将文件信息数据写入
	outputFileHeader.bitmapType = 19778;
	outputFileHeader.bitmapSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + outputLineByteSize * outputInfoHeader.bitmapHeight;
	outputFileHeader.bitmapReserved1 = 0;
	outputFileHeader.bitmapReserved2 = 0;
	outputFileHeader.bitmapOffsets = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	//将图片信息数据写入
	outputInfoHeader.bitmapSize = sizeof(BITMAPINFOHEADER);
	outputInfoHeader.bitmapPlate = inputInfoHeader.bitmapPlate;
	outputInfoHeader.bitCompression = inputInfoHeader.bitCompression;
	outputInfoHeader.bitSizeImage = outputLineByteSize * outputInfoHeader.bitmapHeight;
	outputInfoHeader.bitXPelsPerMeter = inputInfoHeader.bitXPelsPerMeter;
	outputInfoHeader.bitYPelsPerMeter = inputInfoHeader.bitYPelsPerMeter;
	outputInfoHeader.bitColourUsed = inputInfoHeader.bitColourUsed;
	outputInfoHeader.bitColourImportant = inputInfoHeader.bitColourImportant;
	
	//写入到新生成的文件吧
	fwrite(&outputFileHeader, sizeof(BITMAPFILEHEADER), 1, file);
	//fseek(file, sizeof(BITMAP_FILE_HEADER), 0);
	fwrite(&outputInfoHeader, sizeof(BITMAPINFOHEADER), 1, file);
	//fseek(file, sizeof(BITMAP_INFO_HEADER), sizeof(BITMAP_FILE_HEADER));
	fwrite(outputData, outputInfoHeader.bitSizeImage, 1, file);
	
	//收尾工作，关闭文件，释放内存
	free(outputData);
	fclose(file);
	return;
}

void Zoom(const char *ratio) {
	//计算新生成图像像素，长宽信息，每行有几个像素，并为新图片像素信息分配内存地址
	float zoomnumber = atof(ratio) * 1.0 / 100.0;
	outputInfoHeader.bitmapBitCount = inputInfoHeader.bitmapBitCount;
	outputInfoHeader.bitmapWidth = (int)(inputInfoHeader.bitmapWidth * zoomnumber + 0.5);
	outputInfoHeader.bitmapHeight = (int)(inputInfoHeader.bitmapHeight * zoomnumber + 0.5);
	inputLineByteSize = (inputInfoHeader.bitmapWidth * outputInfoHeader.bitmapBitCount + 31 ) / 32 * 4;
	outputLineByteSize = (outputInfoHeader.bitmapWidth * inputInfoHeader.bitmapBitCount + 31 ) / 32 * 4;
	outputData = (unsigned char *)malloc(sizeof(unsigned char) * outputLineByteSize * outputInfoHeader.bitmapHeight);

	//以下使用双线性插值法缩放图像，公式大致如下
	//f(x,y) = f(Q11)(x2-x)(y2-y) + f(Q21)(x-x1)(y2-y) + f(Q12)(x2-x)(y-y1) + f(Q22)(x-x1)(y-y1)
	//其中x,y为要取得的点，Q11,Q12,Q21,Q22为取的四个临近点
 	//BMP像素的存储顺序为从左到右，从下到上(这很坐标系)
	for (int i = 0; i < outputInfoHeader.bitmapHeight; i++) {
		for (int j = 0; j < outputInfoHeader.bitmapWidth; j++) {
			//每个像素有三个颜色数据，也就是能增强电脑性能的RGB三色
			for (int k = 0; k < 3; k++) {
				//先定位一个点
				int i1 = i / zoomnumber;
				int j1 = j / zoomnumber;
				//再找其他两个点
				int i2 = i1 + 1;
				int j2 = j1 + 1;
				//计算需要的数据
				double fx1 = i1 - i1;
				double fx2 = 1.0 - fx1;
				double fy1 = j1 - j1;
				double fy2 = 1.0 - fy1;
				
				double s1 = fx1 * fy1;
				double s2 = (1.0 - fx1) * fy1;
				double s3 = (1.0 - fx1) * (1.0 - fy1);
				double s4 = fx1 * (1.0 - fy1);
				//现在往目标图像数据中写入插值得到的数据
				if ((j1 >= 0) && (j1 < inputInfoHeader.bitmapWidth - 1) && (i1 >= 0) && (i1 < inputInfoHeader.bitmapHeight - 1)) {
					*(outputData + i * outputLineByteSize + j * 3 + k)
				  = *(inputData + i2 * inputLineByteSize + j2 * 3 + k) * s1
			      + *(inputData + i1 * inputLineByteSize + j2 * 3 + k) * s2
			      + *(inputData + i1 * inputLineByteSize + j1 * 3 + k) * s3
				  + *(inputData + i2 * inputLineByteSize + j1 * 3 + k) * s4;
				} else {
					*(outputData + i * outputLineByteSize + j * 3 + k) = 255;
				}
			}
		}
	}
	//释放输入图片的内存
	free(inputData);
}

int main(int argc, char *argv[4]) {
	LoadBmp(argv[1]);
	Zoom(argv[2]);
	SaveBmp(argv[3]);
	return 0;
}
