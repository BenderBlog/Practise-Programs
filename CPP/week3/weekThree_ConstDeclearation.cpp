#include<iostream>
#include<string>
using namespace std;
// https://www.zhihu.com/question/443195492
int main(){
    // '[]' has a higher priorty than &/*
    // A point to a char.
    char ch = 's';
    char *p = &ch;
    // An array of five int.
    int c[5] = {1,2,3,4,5};
    // A refrence to an array of five integers.
    // (&d)[5] ==> an refrence of a int array, 
    // not an array of refrences of int. 
    int (&d)[5] = c;
    // A pointer to an array of char strings.
    string str[3] = {"Barry", "Robin", "Maurice"};
    // an array of a string array,
    // not an array of a string point.
    string (*pstr)[3] = &str;
    // A pointer to a pointer of a char.
    char **c = &p;
    // A constant integer.
    int const lucky = 23;
    // A pointer to a constant int.
    int const * a = &lucky;
    // A constant pointer to an int.
    int evil = 666;
    int * const toInt = &evil;
    // If we see const, read it from right to left.
}