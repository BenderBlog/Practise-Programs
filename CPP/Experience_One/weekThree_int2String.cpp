#include<iostream>
#include<string>

namespace transfer{
    
    typedef std::string string;
    
    string itos(int toTransfer){
        char const table[10] = {'0','1','2','3','4','5','6','7','8','9'};
        string toReturn;
        if (toTransfer == 0){
            toReturn = "0";
        } else if (toTransfer == -2147483648){
            toReturn = "-2147483648";
        } else {
            int toDeal = abs(toTransfer);
            while (toDeal > 0){
                toReturn = table[toDeal % 10] + toReturn;
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
    while (true){
        unsigned int toTransfer;
        std::cin >> toTransfer;
        if (!std::cin) break;
        std::cout << transfer::itos(toTransfer) << std::endl;
    }
}