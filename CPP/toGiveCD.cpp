#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

#include<ctime>

using namespace std;


int main(){
    ifstream file;
    // Read the QQ number of the people who want the CD.
    file.open("list.txt");
    if (!file.good()){
        cout << "File Not Found!" << endl;
    }
    vector<unsigned long> userDictionary;
    unsigned long toInput;
    while (file >> toInput)
        userDictionary.push_back(toInput);
    random_shuffle(userDictionary.begin(),userDictionary.end());
    srand((unsigned)time(NULL));
    // Look for the people randomly.
    int lucky = rand()%userDictionary.size();
    cout << userDictionary[lucky] << endl;
}
