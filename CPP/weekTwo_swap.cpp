#include<iostream>

using namespace std;

void swap_point(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_refrence(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

int main(){
    int a = 23;     // Lucky number of the Bright Side of Me
    int b = 666;    // Lucky number of the Dark Side of Me
    cout << a << " " << b << endl;
    swap_refrence(a,b);
    cout << a << " " << b << endl;
    swap_point(&a,&b);
    cout << a << " " << b << endl;

}