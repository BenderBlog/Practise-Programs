#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct evaling{
    string element;
    int times;
}Eval;

int main(){
    ifstream file;
    file.open("words.txt");
    if (!file.good()){
        cout << "File Not Found!" << endl;
    }
    vector<string> userDictionary;
    string toInput;
    while (file >> toInput)
        userDictionary.push_back(toInput);

    sort(userDictionary.begin(),userDictionary.end());
    vector<string>::iterator t = userDictionary.begin();
    
    vector<Eval> toOutput;
    while (t!=userDictionary.end()){
        Eval input;
        input.element = *t;
        input.times = 1;
        while (true){
            t++;
            if (*t == input.element){
                input.times ++;
            } else {
                toOutput.push_back(input);
                break;
            }
        }
    }
    cout << "Total words: " << toOutput.size() << ". Details as follow:" << endl;
    vector<Eval>::iterator te = toOutput.begin();
    for (te; te!=toOutput.end(); ++te){
        Eval temp = *te;
        cout << temp.element << "\t" << temp.times << endl;
    }
}
