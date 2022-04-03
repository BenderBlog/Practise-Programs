// Compile: g++ weekFive_sortTree.cpp tree.cpp -o whatever
// Execute: ./whatever
// Interrupt input in UNIX-Like: Ctrl+D

#include "tree.hpp"
using namespace sortTree;
int main()
{
    tree T;
    std::string words;
    while (std::cin >> words)
    {
        T.addNode(words);
    }
    std::cout << std::endl;
    T.showTree();
    std::cout << std::endl;
    T.sort();
    T.free();
    return 0;
}