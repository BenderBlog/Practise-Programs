#include<string>
#include<map>
#include<iostream>

using namespace std;

struct whatdata {
    int count;
    double total;
    whatdata(){
        count=0;
        total=0;
    }
    whatdata(int c, double t){
        count=c;
        total=t;
    }
};

int main(){
    map<string, whatdata> dict;
    int count;
    int total = 0;
    cin >> count;
    for (int i = 0; i < count; ++i){
        string name;
        double value;
        cin >> name >> value;
        if (dict.find(name) == dict.end()){
            dict[name] = whatdata(1, value);
        } else {
            dict[name].count++;
            dict[name].total += value;
        }
        total += value; 
    }
    for (auto it = dict.begin(); it != dict.end(); ++it){
        cout << it->first << " " << it->second.count << " " << it->second.total << " " << it->second.total/it->second.count << endl;
    }
    cout << "Total: " << total << endl;
    return 0;  
}