#include "error.h"
#include "lexer.h"
#include <string>
#include <iostream>

int Error::no_of_errors = 0;

double Error::error(int n, const string &str)
{
    no_of_errors++;
    int a = Lexer::lines;
    // cout << "Dealing with " << Lexer::lastMemory << endl;
    if (Lexer::lastMemory == '\n')
    {
        // Avoid the situation, which is, the entire line had read,
        // including the terminate node, but find error at last.
        // For example, 1/0
        // Although use class is the best solution, but fuck jwc.
        a -= 1;
    }
    std::cerr << "Line " <<  a << " got error: " + str << std::endl;
    Lexer::curr_tok = Lexer::ERR;
    return n;
}
