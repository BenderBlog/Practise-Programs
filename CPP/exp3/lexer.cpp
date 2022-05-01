#include <iostream>
#include "lexer.h"
#include "error.h"

using namespace std;
using namespace Lexer;
using namespace Error;

Lexer::Token_value Lexer::curr_tok;//the value that get_token() get last time
double Lexer::number_value;//save NUMBER's value
string Lexer::string_value;//save NAME's value
vector<string> Lexer::fileNames;
istream *Lexer::input = nullptr;

//input
Lexer::Token_value Lexer::get_token() {
    char ch = 0;
    do {
        if (!Lexer::input->get(ch)) {
            if (Lexer::PRINT != curr_tok) {
                return curr_tok = PRINT;
            }
            if (switch_input() != 0) {
                return curr_tok = END;
            } else {
                ch = ' ';
                continue;
            }
        }
    } while (ch != '\n' && isspace(ch));//skip whitespace except ’\n’

    switch (ch) {
        //let ';' equals to '\n'
        case ';':
        case '\n':
            return curr_tok = PRINT;
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return curr_tok = Token_value(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            cin.putback(ch);
            cin>>number_value;
            return curr_tok = NUMBER;
        default: { //NAME, NAME=, or error
            if (isalpha(ch)) {
                string_value = ch;
                while (cin.get(ch) && isalnum(ch)) {
                    string_value.push_back(ch);//Read the string type one by one.
                }
                cin.putback(ch);//read one more word to do isalnum(ch),so put it back.
                return curr_tok = NAME;
            } else {
                error(-1, "bad token");
                return curr_tok = PRINT;
            }
        }
    }
}

int Lexer::parseCommandLine(int argc, char **argv) {
    if (argc == 1) {
        Lexer::input = &cin;
        return 0;
    } else {
        for (int i = 1; i < argc; ++i) {
            fileNames.emplace_back(argv[i]);
            Lexer::input = new ifstream(fileNames[0].c_str());
            if (Lexer::input->good()) {
                fileNames.erase(fileNames.begin());
            } else {
                return -1;
            }
        }
    }
    return 1;
}

int Lexer::switch_input() {
    if (fileNames.empty()) {
        return 1;
    } else {
        delete Lexer::input;
        Lexer::input = new ifstream(fileNames[0].c_str());
        if (Lexer::input->good()) {
            fileNames.erase(fileNames.begin());
        } else {
            return -1;
        }
    }
    return 1;
}

void Lexer::skip() {
    no_of_errors++;
    while (*input) {
        char ch;
        input->get(ch);
        switch (ch) {
            case 'n':
            case ';':
                return;
        }
    }
}


