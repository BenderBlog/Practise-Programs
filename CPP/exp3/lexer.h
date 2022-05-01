#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace Lexer {
    enum Token_value { //all tokens
        NAME, NUMBER, //Their value would be saved in number_value or string_value.
        END, ERR,
        PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
        PRINT = ';', ASSIGN = '=', LP = '(', RP = ')',
    };

    //(defined in lexer.cpp mostly)
    extern Token_value curr_tok;//the value that get_token() get last time

    extern double number_value;//save NUMBER's value
    extern string string_value;//save NAME's value

    extern istream *input;// input stream controller
    extern vector<string> fileNames;

    extern Token_value get_token();//input

    extern int parseCommandLine(int argc, char *argv[]);

    extern int switch_input();

    extern void skip();
}
#endif //LEXER_H
