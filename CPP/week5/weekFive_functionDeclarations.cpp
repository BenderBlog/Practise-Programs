#include<iostream>
using namespace std;
// a function taking arguments of type pointer to character and refrence to integer and returning no value
void print(char *str, int &num)
{
    cout << "The string is: " << str << endl;
    cout << "The number is: " << num << endl;
}
// a pointer to such a function;
// We know that in cpp, a pointer to a function needs formal parameter.
void (*ptr)(char *, int &);
// a function taking such a pointer as an argument;
void print2(void (*ptr)(char *, int &))
{
    char str[] = "Hello";
    int num = 10;
    ptr(str, num);
}
// a function returning such a pointer.
void (*returnPtr())(char *, int &)
{
    return print;
}

