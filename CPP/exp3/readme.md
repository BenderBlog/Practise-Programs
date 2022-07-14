## 实验目的
通过这次实验，我要通过更改桌面计算器程序，进一步熟悉模块化编程的思想。

## 实验环境
操作系统：Arch Linux  
开发工具：VSCode + clang++

## 实验内容
给桌面计算机魔改上以下功能：
1. 多头文件，多源文件。
2. 行数统计以及错误提示
3. 命令行输入 + 多文件输入

## 数据结构与算法说明

### 源代码结构
1. main.cpp：主程序，也就是程序。
2. lexer.hpp：语法处理器。
3. paraser.hpp：计算器。
4. error.hpp：错误处理。
5. sym.h：存储变量。

### 我添加的变量
1. char Lexer::lastMemory：上一个分析的字符。
2. int Lexer::lines = 1：输入的行数，兼职正在分析的行数，所以从一开始计数。
3. 语句结束符：';' 和 \n'

### 行数统计实现

1. 自然地，在每次侦测到语句结束符的时候，增加一次。无论是正常结束还是错误侦测到之后。

2. 注意一下，如果出现多个结束字符的时候，我们要特殊处理，防止多个结束字符连在一起搞乱了。

   ```c++
// From Lexer.cpp Line 49 
if (( ch == '\n' || ch == ';' ) && ( lastMemory == '\n' || lastMemory == ';'))
{
   lines--;
}
	```

3. 还有，在结束读取文件的时候，考虑是不是要把最后一个字符为回车的情况给搞掉。

	```c++
   if (switch_input() != 0)
   {
   // Not let the last end charactor count the line.
   	if ( lastMemory == '\n' || lastMemory == ';')
   	{
   		lines--;
   	}
       return curr_tok = END;
   }
	```
### 错误提示

本处提供我的错误处理函数处理方式。

首先，发现错误的时候，调用错误输出函数，然后函数进行计数，然后输出错误。错误行数直接从 Lexer 中获取，不过要注意，如果是回车后报错的，输出时候的行数减去一。

```c++
double Error::error(int n, const string &str)
{
    no_of_errors++;
    int a = Lexer::lines;
    // cout << "Dealing with " << Lexer::lastMemory << endl;
    if (Lexer::lastMemory == '\n')
    {
        // Avoid the situation, which is, the entire line had read,
        // including the terminate node, but find error at last.
        // For example, 1/0
        // Although use class is the best solution, but fuck jwc.
        a -= 1;
    }
    std::cerr << "Line " <<  a << " got error: " + str << std::endl;
    Lexer::curr_tok = Lexer::ERR;
    return n;
}
```

### 多文件输入
在命名空间 Lexer 下面定义一个 instream，称之为 input，如果没有文件输入，直接搞到标准输入。否则循环读取文件。行数的变化不会因文件读取的切换而出现变化。半截出现读取故障，会结束整个程序。


## 测试用例与测试结果

* 编译方法：make
* 测试样例：两个 test_script_*.txt
* 测试结果
```bash
[superbart@superbart-laptop source_3_1]$ make
clang++ -o error.o -c error.cpp
clang++ -o lexer.o -c lexer.cpp
clang++ -o main.o -c main.cpp
clang++ -o parser.o -c parser.cpp
clang++ -o sym.o -c sym.cpp
clang++ error.o lexer.o main.o parser.o sym.o -o cal
rm -rf *.o
[superbart@superbart-laptop source_3_1]$ ./cal ../test_script_first.txt ../test_script_second.txt
../test_script_first.txt reads OK!
Line 1 result is 2.71828
Line 2 result is 3.14159
Line 3 got error: bad token
Line 3 got error: primary expected
Line 4 result is 5.71828
Line 5 got error: divide by 0
Line 6 result is 132
../test_script_second.txt reads OK!
Line 7 result is 2.03432e+06
Line 8 result is 3
Line 9 result is 31.4159
Line 10 result is 32.0826
Line 11 got error: divide by 0
Inputted line: 11
Error found: 4
[superbart@superbart-laptop source_3_1]$ 
```

## 实验总结
通过本次实验，我对 CPP 模块化编程更加深入的了解。根据对这个计算器的修改，知道了牵一发而动全身的道理，要求我们对整个计算器程序的每个部分都要有了解，以及知道原理。