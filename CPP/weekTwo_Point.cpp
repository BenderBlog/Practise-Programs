#include<iostream>
using namespace std;

int main(){
    char ch;
    int  size;
    double price; 
    int arr[5];
    char *pChar = &ch;
    int *pInt  = &size;
    double *pDbl  = &price;
    int (*pArr)[5] = &arr;
    cout << (int *)pChar <<"\t" << (int *)(pChar+1) << endl;
    cout << (int *)pInt <<"\t" << (int *)(pInt+1) << endl;
    cout << (int *)pDbl <<"\t" << (int *)(pDbl+1) << "\t" << sizeof(double) << endl;
    cout << (int *)pArr <<"\t" << (int *)(pArr+1) << "\t" << sizeof(arr) << endl;
}


