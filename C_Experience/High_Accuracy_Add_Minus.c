//2021 SuperBart@Bilibili Under The Unlicense
//程序课程作业1 高精度运算 本质就是竖式加减法
//减法是相当恶心啊！

#include <stdio.h>
#include <string.h>
//C语言的函数不能返回数组，所以只能在此定义全局数组
//static int 数组个人认为会导致代码不容易理解
int solution[101];

//minus和add有互相调用情况，故在此加入，防止隐式警告
int output(int *solution);
void minus(int *first, int *second);
void add(int *first, int *second);
void translate(char *input, int *result);

int main(int argc, char *argv[])
{
	//数组初始化为-1，相当于标记为空数组，因为数字中或许有0
	int numberFirst[101], numberSecond[101];
	for (int i = 0; i < 101; ++i)
	{
		numberFirst[i] = -1;
		numberSecond[i] = -1;
		solution[i] = -1;
	}

	//这里我使用了命令行式输入，为了练习该种方式
	printf("高精度运算程序，可计算100位数字\n");
	if (argc == 2 && strcmp(argv[1], "help") == 0)
	{
		printf("用法: count [选项] [数字] [数字]\n");
		printf("选项：\n  add	两个数累加，之后为两个数字，以空格分开\n");
		printf("  minus	两个数相减，之后为两个数字，以空格分开\n");
		printf("  help	显示这个帮助信息:-)\n");
		printf("实例用法: count add 22 -33\n");
		return 0;
	}
	else if (argc == 4 && strcmp(argv[1], "add") == 0)
	{
		translate(argv[2], numberFirst);
		translate(argv[3], numberSecond);
		add(numberFirst, numberSecond);
	}
	else if (argc == 4 && strcmp(argv[1], "minus") == 0)
	{
		translate(argv[2], numberFirst);
		translate(argv[3], numberSecond);
		minus(numberFirst, numberSecond);
	}
	else
	{
		printf("\n抱歉，我摸不透你的心:-P\n请使用 help 获取帮助\n");
		return 0;
	}
}
//以下output函数用来输出solution
int output(int *solution)
{
	printf("结果为: ");
	//判断数字的正负
	if (solution[0] == 1)
		printf("-");
	//鉴于存储数字方式与我们人正常读取方向不同，在此得由大元素到小元素循环
	for (int i = 100; i > 0; --i)
	{
		//略过-1项目，即空项目
		if (solution[i] == -1)
			continue;
		else
			printf("%d", solution[i]);
	}
	printf("\n");
	return 0;
}
//以下translate函数是用来将输入的字符串转换成数字数组
void translate(char *input, int *result)
{
	//数字数组第一个元素用来表示数字的正负
	//输入数字为负数，则标记1；否则，标记为0
	if (input[0] == '-')
		result[0] = 1;
	else if (input[0] != '-')
		result[0] = 0;

	//在这里我将数字的排列顺序改成“个 十 百 千......”
	//方便接下来的运算
	int j = 1;
	for (int i = strlen(input) - 1; i >= result[0]; --i)
	{
		result[j] = input[i] - 48;
		j = j + 1;
	}
}
//以下minus函数用来处理减法
void minus(int *first, int *second)
{
	//同号的话，可以进行减法运算，注意减法的前后顺序不可颠倒
	if (first[0] == second[0])
	{
		//先比两数绝对值大小
		int max = 0;
		for (int i = 1; first[i] != -1 || second[i] != -1; ++i)
		{
			if (first[i] > second[i])
				max = 1;
			else if (first[i] < second[i])
				max = 2;
			else if (first[i] == second[i])
				continue;
		}
		//根据两数绝对值大小情况，判断如何使绝对值相减为正数，然后将两数绝对值进行相减。
		//若绝对值相同，直接等于零；否则进行下一步判断。
		if (max == 0)
		{
			solution[0] = 0;
			solution[1] = 0;
		}
		else
		{
			//在此定义两个指针，用来表示绝对值大/小的数组，节约行数
			int *a, *b;
			//把最大绝对值的和最小绝对值的数用指针放在第一个
			if (max == 1)
			{
				a=first;
				b=second;
			}
			else if (max == 2)
			{
				a=second;
				b=first;
			}
			//然后进行真正的逐位相减
			for (int i = 1; a[i] != -1 || b[i] != -1; ++i)
			{
				//如果出现位数较另一个数多的情况，将-1改成0
				if (a[i] == -1)
					a[i] = 0;
				else if (b[i] == -1)
					b[i] = 0;
				//现在该相减了
				solution[i] = a[i] - b[i];
				//检查借位情况，模拟真正的借位，跳过零，设为9
				if (solution[i] < 0)
				{
					solution[i] += 10;
					for (int j=i+1; a[j] != -1 || b[j] != -1; ++j){
						if (a[j] == 0) 
							a[j] = 9;
						else if (a[j] != 0){
							a[j] -= 1;break;
						}
					}
				}
			}
			//然后判断结果的正负值
			if ((max==1 && a[0]==0)||(max==2 && a[0]==1)) solution[0] = 0;
			else if ((max==1 && a[0]==1)||(max==2 && a[0]==0)) solution[0] = 1;
			//最后，将没有用的0全部去掉
			for (int i = 100; i > 0; --i){
				if (solution[i] == -1)
					continue;
				else if (solution[i] == 0)
					solution[i] = -1;
				else if (solution[i] != 0 && solution[i] != -1 && solution[i-1] != -1)
					break;
			}
		}
		output(solution);
	}
	//要是异号的话，找加法玩去吧，别来烦我了:-!
	//当然，在此之前，数字要按照第一个数同号
	else if (first[0] != second[0])
	{
		if (first[0] == 1 && second[0] == 0)
		{
			second[0] = 1;
			add(second, first);
		}
		else if (first[0] == 0 && second[0] == 1)
		{
			second[0] = 0;
			add(first, second);
		}
	}
}
//以下add函数用来表示加法
void add(int *first, int *second)
{
	//同号的话，可以进行加法运算，加法的前后顺序可以颠倒，所以实现相对简单一些
	if (first[0] == second[0])
	{
		//同号情况下，加法的结果和被累加数相同
		solution[0] = first[0];
		//然后进行逐位加法，外置的int是因为要判断最后一位的情况
		int i;
		for (i = 1; first[i] != -1 || second[i] != -1; ++i)
		{
			//如果出现位数较另一个数多的情况，将-1改成0
			if (first[i] == -1)
				first[i] = 0;
			if (second[i] == -1)
				second[i] = 0;
			//然后是真正的加法
			solution[i] += first[i] + second[i] + 1;
			//判断进位情况
			if (solution[i] >= 10)
			{
				solution[i] = solution[i] % 10;
				solution[i + 1] += 1;
			}
		}
		//累加时最大位容易进位后没有加成1，所以在此判断最大位情况
		if (solution[i] == 0)
			solution[i] = 1;

		output(solution);
	}
	//没想到加法也是对异号同样的不耐烦，看样子都不喜欢当电灯泡:-P
	else if (first[0] != second[0])
	{
		if (first[0] == 1 && second[0] == 0)
		{
			first[0] = 0;
			minus(second, first);
		}
		else if (first[0] == 0 && second[0] == 1)
		{
			second[0] = 0;
			minus(first, second);
		}
	}
}
