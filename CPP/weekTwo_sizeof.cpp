#include<iostream>

using namespace std;

int main(){
    cout << "sizeof short\t" << sizeof(short) << endl;
    cout << "sizeof int\t" << sizeof(int) << endl;
    cout << "sizeof long\t" << sizeof(long) << endl;
    cout << "sizeof long long\t" << sizeof(long long) << endl; // C++ 11 later only
    cout << "sizeof unsigned short\t" << sizeof(unsigned short) << endl;
    cout << "sizeof unsigned int\t" << sizeof(unsigned int) << endl;
    cout << "sizeof unsigned long\t" << sizeof(unsigned long) << endl;
    cout << "sizeof unsigned long long\t" << sizeof(unsigned long long) << endl; // C++ 11 later only
    cout << "sizeof char\t" << sizeof(char) << endl;
    cout << "sizeof wchar_t\t" << sizeof(wchar_t) << endl;
    cout << "sizeof float\t" << sizeof(float) << endl;
    cout << "sizeof double\t" << sizeof(double) << endl;
    cout << "sizeof long double\t" << sizeof(long double) << endl;
    cout << "sizeof void *\t" << sizeof(void*) << endl;// Point are the same.
    cout << "sizeof char *\t" << sizeof(char*) << endl;// See?
    struct mess{
        int a;
        int b;
    };
    cout << "sizeof struct \"mess\" which contain 2 integer\t" << sizeof(mess) << endl;
    union floatWithLong{
        long a;
        float b;
    };
    union floatWithLong c;
    c.a = 10000L;
    cout << "sizeof union \"floatWithLong\" which contain long\t" << sizeof(union floatWithLong) << endl;
    c.b = 1145141919.81;
    cout << "sizeof union \"ffloatWithLong\" which contain float\t" << sizeof(union floatWithLong) << endl;
    enum genesis {Peter_Gabriel, Phil_Collins, Tony_Banks, Mick_Rutherford, Steve_Hackett};
    cout << "sizeof enum \"genesis\" " << sizeof(genesis) << endl;
}