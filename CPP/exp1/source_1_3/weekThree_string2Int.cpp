/*
    2021 SuperBart, relesed under SuperBart Public Domain Software License.
    Question:
        Write a function atoi(const char*) that takes a string containing
        digits and returns the corresponding int. For example, atoi("123")
        is 123. Modify atoi() to handle C++ octal and hexadecimal notation
        in addition to plain decimal numbers. Modify atoi() to handle the
        C++ character constant notation.
    Notice:
        I use the STL string container.
*/

#include <iostream>
#include <string>

namespace transfer
{

    typedef std::string string;

    int stoi(string toTransfer)
    {
        int toReturn = 0;
        int i = 0;
        bool isNegative = false;
        if (toTransfer[0] == '-')
        {
            isNegative = true;
            i = 1;
        }
        else if (toTransfer[0] == '+')
        {
            isNegative = false;
            i = 1;
        }
        // First Dec2Int, then Hex2Int, last Octal2Int
        if (toTransfer[i] != '0' && toTransfer.size() != 1)
        {
            for (i; i < toTransfer.size(); ++i)
            {
                toReturn = toTransfer[i] - '0' + toReturn * 10;
            }
        }
        else if (toTransfer[++i] == 'x' or toTransfer[i] == 'X')
        {
            for (++i; i < toTransfer.size(); ++i)
            {
                int toAdd;
                // Treat A(a)-E(e) as 10-15.
                // These offset are based on the ASCII Table.
                if (toTransfer[i] >= 'A' && toTransfer[i] <= 'Z')
                    toTransfer[i] -= 55;
                else if (toTransfer[i] >= 'a' && toTransfer[i] <= 'z')
                    toTransfer[i] -= 87;
                else
                    toTransfer[i] -= 48;
                toReturn = toTransfer[i] + toReturn * 16;
            }
        }
        else
        {
            for (i; i < toTransfer.size(); ++i)
            {
                toReturn = toTransfer[i] - '0' + toReturn * 8;
            }
        }
        isNegative ? toReturn = -toReturn : toReturn = toReturn;
        return toReturn;
    }
};

// Quit using Ctrl+D
int main()
{
    while (true)
    {
        std::string a;
        std::cin >> a;
        if (!std::cin)
            break;
        std::cout << transfer::stoi(a) << std::endl;
    }
}
