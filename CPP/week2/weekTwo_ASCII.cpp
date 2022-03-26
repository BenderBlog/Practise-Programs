#include<iostream>
#include<cstdio>

using namespace std;

int main(){
    printf("char\tinteger\thexadecimal\n");
    for (int i = 32; i < 127; ++i){
        printf("%c\t%d\t%x\n",i,i,i);
    }
}
