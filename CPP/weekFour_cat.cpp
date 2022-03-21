#include<iostream>
#include<fstream>

using namespace std;

void print(ifstream& eval){
    string tmp;
    while (getline(eval,tmp)){
        cout << tmp << endl;
    }
}

int main(int argc, char *argv[]){
    for (int i = 1; i < argc; ++i){
        ifstream input;
        input.open(argv[i]);
        if (!input.good()){
            cout << argv[i] << " connot open, skip." << endl;
            continue;
        } else {
            cout << argv[i] << " as follow:"<< endl;
            print(input);
            cout << endl;
        }
    }
}
