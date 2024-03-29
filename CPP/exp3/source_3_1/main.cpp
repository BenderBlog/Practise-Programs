#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "error.h"
#include "sym.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (Lexer::parseCommandLine(argc, argv) != 0)
    {
        Error::error(-1, "A file read failed...\nInterrupt the entire process!");
        return 1;
    }
    // constants
    Symbol_table::table["pi"] = 3.1415926535897932385;
    Symbol_table::table["e"] = 2.7182818284590452354;

    while (Lexer::get_token() != Lexer::END)
    {
        if (Lexer::curr_tok == Lexer::PRINT)
            continue;
        if (Lexer::curr_tok == Lexer::ERR)
        {
            Lexer::skip();
            continue;
        }
        double value = Parser::expr(false); // calculate
        switch (Lexer::curr_tok)
        {
        case Lexer::PRINT:
        case Lexer::END:
            cout << "Line " << Lexer::lines - 1 << " result is " << value << endl;
            continue;
        case Lexer::ERR:
            Lexer::skip();
            continue;
        default:
            Error::error(Lexer::curr_tok, "may need expression ending");
            Lexer::skip();
            continue;
        }

    }
    if (Lexer::input != &std::cin)
    {
        delete Lexer::input;
    }
    cout << "Inputted line: " << Lexer::lines - 1 << endl;
    cout << "Error found: " << Error::no_of_errors << endl;
    return 0;
}
