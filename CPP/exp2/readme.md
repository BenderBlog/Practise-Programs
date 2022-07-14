## 实验目的
通过这次实验，我要掌握函数的传参和不定参数的处理。以及一些模块化编程思想。

## 实验环境
操作系统：Arch Linux  
开发工具：VSCode + GCC

## 实验内容
1. 输入多个参数，然后对每一个参数打招呼。
2. 根据已定链表树的数据结构，写一个对字符串的二叉排序树。
3. 不用 `printf()` 函数，运用 `cstdarg` 库实现类似该函数的 `error()`。
4. 写一个日期类，然后能添加日期/月份/年份，判断天数对应星期，然后其之后下一周的周一。

## 数据结构与算法说明

### 输入多个参数，然后对每一个参数打招呼

* 模块结构及文件组织设计：
模块 1： main()函数，包括了读取数据和计算。
* 算法:
  通过终端输入的参数，逐个输出。此处直接引用我写过的[博客](https://www.superbart.xyz/p/linux-in-quick-run.html "博客")：
>各位应该在C语言程序设计中，学到了如何通过命令行输入参数，而不是先把程序执行了，再输入数据。你们当时肯定输入的是这个：
`int main(int argc, char* argv[])`
其中第一个参数argc(argument count)，是你输入的参数数量。第二个参数argv(argument vector)，存放的是你输入的参数字符串。举个例子，前面我们提到要搞软件包管理。在Ubuntu下，你搜索软件包(举个例子，gcc编译器)的时候，你输入的是：
`apt search gcc`
这样，你输入了三个参数，一个是apt，一个是search，一个是gcc。这样的话，argc的数值是3，而argv里面存储的，则是那三个参数的字符串了。


### 根据已定链表树的数据结构，写一个对字符串的二叉排序树。

* 模块结构及文件组织设计：  
模块 1：sortTree 命名空间，包括 Tnode 数据结构和 tree 类。实现在 tree.cpp 。
模块 2：weekFive_sortTree.cpp 包括 main 函数。

* 关键数据结构设计：
1. struct Tnode:
```C
    struct Tnode
    {
        std::string word;
        int count;
        Tnode *left;
        Tnode *right;
    };
```
2. class tree:
```C
    class tree
    {
    private:
        // Implement.
        Tnode *m_T;
        void forAdd(Tnode *&t, std::string words);
        void forShow(Tnode *t);
        void forSort(Tnode *t);
        void forFree(Tnode *&t);

    public:
        // Interface.
        tree();
        void addNode(std::string words);
        void showTree();
        void sort();
        void free();
    };
```
* 算法

 1. void forAdd(Tnode *&t, std::string words);

    生成一个树节点，根据排序二叉树的方式找到对应位置，然后插入/计数加一。

    如果树是空的话就生成这个树的根节点。

 2. void forShow(Tnode *t);

    树的先序遍历展示。

 3. void forSort(Tnode *t);

    树的中序遍历展示，根据二叉排序树的特性，是一个倒序排列。

 4. void forFree(Tnode *&t);

    树的后序遍历，删除节点。

### 不用 `printf()` 函数，运用 `cstdarg` 库实现类似该函数的 `error()`。
* 函数原型
```C
void error(const char *format, ...)
```
*  算法
1. 生成 `va_list` 对象，然后初始化。
2. 通过对母字符串的逐个字符读取，判断以下情况:
	* 如果不是 `%` 直接输出。
	* 如果是 `%`， 后面跟着是：
	| 输入 | 输出    |
	| :--: | :-----: |
	|  s   | 字符串  |
	|  c   | 字符    |
	|  d   | 整型数  |
	|  %   | `%`符号 |
3. 注意判断字符还是整数的时候，先按照整型数读入，然后按情况强制类型转换看看。

* `cstdarg` 函数库怎么搞不定长形参的？
1. 形参的最后一定要是省略号。
2. `va_list` 规定一个不定长形参变量。
3. `va_start` 让其找到开始位置，之后 `va_arg` 向后读取一个参数。
4. `va_end` 终止 `va_list` 存在。

### 写一个日期类，然后能添加日期/月份/年份，判断天数对应星期，然后其之后下一周的周一
* 模块结构及文件组织设计： 
1. date.hpp 写了类文件和 `<<` 操作符重载。
2. date.cpp 写了函数的具体实现和 main 函数。

* 关键数据结构设计：
```C
    class Date
    {
    private:
        int m_year;
        int m_month;
        int m_day;
        bool isLeap() const;
        int dayInMonth() const;
        int dayInYear() const;
        int startWeek() const;

    public:
        Date(int year = 1970, int month = 1, int day = 1);
        void print();
        void addDay();
        void addMonth();
        void addYear();
        int evalWeek();
        friend ostream &operator<<(ostream &os, const Date &here);
        void nextWeek();
    };
```

* 算法： 
  1. `int Date::startWeek()`
      先设定“2021-1-1 周五”为基准日，然后寻找之前年的一月一日和基准日之间差了多少天。   
      如果是在2021年及之前，返回值为 `abs(levelWeek - totalDay % 7)` 。   
      如果在2021年之后，则是 `abs(levelWeek + totalDay % 7) % 7 + 1`  。   
      注意，周日返回的值为 0 。
  
	```C++
  int Date::startWeek() const
  {
      int levelWeek = 5, totalDay = 0; // The standard is 2021-1-1 Friday
      if (m_year - 2021 <= 0)
      {
          for (int i = m_year; i < 2021; ++i)
          {
              if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
              {
                  totalDay += 366;
              }
              else
              {
                  totalDay += 365;
              }
          }
          return abs(levelWeek - totalDay % 7);
      }
      elseabs(levelWeek + totalDay % 7) % 7 + 1
      {
          for (int i = m_year - 1; i > 2021; --i)
          {
              if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
              {
                  totalDay += 366;
              }
              else
              {
                  totalDay += 365;
              }
          }
          int toReturn = abs(levelWeek + totalDay % 7) % 7 + 1;
          if (toReturn == 7)
	            toReturn = 0;
          return toReturn;
      }
  }
  ```
  2. `int Date::evalWeek()`
  	计算这一天是这一年的第几天，加上该年第一天对应星期几减去一的结果余七。
  ```C
  int Date::evalWeek()
  {
    int count = startWeek() - 1;
    // cout << count << endl;
    for (int currentMonth = 1; currentMonth < m_month; ++currentMonth)
    {
        if (currentMonth == 2 && isLeap())
            count += 29;
        else if (currentMonth == 2 && !isLeap())
            count += 28;
        else if (currentMonth == 1 || currentMonth == 3 || currentMonth == 5 ||
                 currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
            count += 31;
        else
            count += 30;
        // cout << count << endl;
    }
    // cout << (count + m_day) << endl;
    return (count + m_day) % 7;
  }
  ```

  3. `void nextWeek()`
  	先强制加一，然后累加到是周一了。

  ```C
  void Date::nextWeek()
  {
    addDay();
    while (evalWeek() != 1)
    {
        addDay();
    }
  }

## 测试用例与测试结果

2. 根据已定链表树的数据结构，写一个对字符串的二叉排序树。
```bash
[superbart@superbart-laptop source_2_2]$ make && ./out
clang++ -o tree.o -c tree.cpp
clang++ tree.o weekFive_sortTree.o -o out
Abcde
dref
daf
ogid
onnobaufb
efe
qoodn
mnebh
sfehu
as


Showing...
Abcde: 1
dref: 1
daf: 1
as: 1
ogid: 1
efe: 1
mnebh: 1
onnobaufb: 1
qoodn: 1
sfehu: 1


Sorting...
Abcde: 1
as: 1
daf: 1
dref: 1
efe: 1
mnebh: 1
ogid: 1
onnobaufb: 1
qoodn: 1
sfehu: 1
[superbart@superbart-laptop source_2_2]$ 
```
3. 不用 `printf()` 函数，运用 `cstdarg` 库实现类似该函数的 `error()`。
```C
int main()
{
    error("Hello %s, %d, %c. %%\n", "SuperBart", 'f', 'f');
    // For test.
    printf("Hello %s, %d, %c. %%\n", "SuperBart", 'f', 'f');
}
```
```bash
[superbart@superbart-laptop source_2_3]$ clang++ errorOutput.cpp -o errorOutput 
[superbart@superbart-laptop source_2_3]$ ./errorOutput
Hello SuperBart, 102, f. %
Hello SuperBart, 102, f. %
[superbart@superbart-laptop source_2_3]$ 
```
4. 写一个日期类，然后能添加日期/月份/年份，判断天数对应星期，然后其之后下一周的周一。
```bash
[superbart@superbart-laptop source_2_4]$ make && ./out 
clang++ -o date.o -c date.cpp
clang++ date.o -o out
1 2019-12-23
1 2019-12-30
2 2019-12-31
5 2020-1-31
6 2020-2-29
0 2021-2-28
1 2021-3-1
5 2022-12-23
1 2022-12-26
2 2022-12-27
5 2023-1-27
1 2023-2-27
2 2024-2-27
1 2024-3-4
[superbart@superbart-laptop source_2_4]$ 
```
## 实验总结
通过本次实验，我对 CPP 模块化编程和过程式编程有了更加深入的了解，并初步接触到了按类编程的方便性与复杂性。