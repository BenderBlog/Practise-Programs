#include<iostream>
#include<string>

namespace transfer{
    
    using namespace std;

    int stoi(string toTransfer){
        int toReturn = 0;
        if (toTransfer[0] != '0' && toTransfer.size() != 1){
            for (int i = 0; i < toTransfer.size(); ++i){
            //cout << toTransfer[i] - '0' << endl;
            toReturn = toTransfer[i] - '0' + toReturn * 10;
            //cout << toReturn << endl << endl;
            }
        } else {
            if (toTransfer[1] == 'x'){
                for (int i = 2; i < toTransfer.size(); ++i){
                    int toAdd;
                    (toTransfer[i] >= 'A' && toTransfer[i] <= 'Z') ? toTransfer[i] -= 55 : toTransfer[i] -= '0';
                    toReturn = toTransfer[i] + toReturn * 16;
                }
            } else {
                for (int i = 1; i < toTransfer.size(); ++i){
                    toReturn = toTransfer[i] - '0' + toReturn * 8;
                }
            }
        }

        if (toTransfer[0] == '-'){
            toReturn *= -1;
        }
        return toReturn;
    }

    string itos(int toTransfer){
        char const table[10] = {'0','1','2','3','4','5','6','7','8','9'};
        string toReturn;
        if (toTransfer == 0){
            toReturn = "0";
        } else {
            int toDeal = abs(toTransfer);
            while (toDeal > 0){
                toReturn = table[toDeal % 10] + toReturn;
                // cout << toReturn << endl;
                toDeal /= 10;
            }
            if (toTransfer < 0){
                toReturn = "-" + toReturn;
            }
        }
        return toReturn;
    }
};

// Only unsigned int :-P
int main(){
    std::string test;
    std::cin >> test;
    std::cout << transfer::stoi(test) << std::endl;
    unsigned int a;
    // Only decimal
    std::cin >> a;
    std::cout << transfer::itos(a) << std::endl;
}