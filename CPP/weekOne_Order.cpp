#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;
int main(){
    vector<int> array;
    int input;
    while(cin >> input){
        array.push_back(input);
    }
    vector<int>::iterator t;
    sort(array.begin(),array.end());
    for (t = array.begin(); t!=array.end(); t++)
        cout << *t ;
}
