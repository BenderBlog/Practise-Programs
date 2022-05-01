#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "sym.h"

using namespace Lexer;
using namespace Error;
using namespace Symbol_table;
//These three functions execute each other,so they need statement first.
//Here using namespace is enough.
//I have no idea weather it is author's intention to help us learning the usage of statement.

//handle + -
double Parser::expr(bool get) {//TIPS:calculation should start by this function.
    double left = Parser::term(get);//Jump to term first,while try to get the first value.
    for (;;) {
        switch (curr_tok) {
            //reason to execute term:
            // if next calculate is * or / , do * or / first.
            case PLUS:
                left += Parser::term(true);
                break;
            case MINUS:
                left -= Parser::term(true);
                break;
            default:
                return left;//just return the read value
        }
    }
}
//handle * /
double Parser::term(bool get) {
    double left = Parser::prim(get);//This line can get value of defined type from prim().
    for (;;) {
        switch (curr_tok) {
            //reason to execute prim:
            // if next calculate is + or - ,
            // instead of do that immediately (which is wrong),
            // we should check the "()".
            case MUL:
                left *= Parser::prim(true);
                break;
            case DIV:
                if (double d = Parser::prim(true)) {
                    left /= d;
                    break;
                } else return error(-1, "divide by 0");
            default:
                return left;//just return the read value
        }
    }
}
//handle primaries
double Parser::prim(bool get) {
    if (get) get_token();//the next value wouldn't be read here,unless the next formula is independent(highest priority).

    switch (curr_tok) {
        case NUMBER: { //floating-point constant
            double v = number_value;//?
            get_token();
            return v;
        }
        case NAME: {
            double &v = table[string_value];
            if (get_token() == ASSIGN)
                v = Parser::expr(true);//Calculate the NAME v's value.
            return v;
        }
        case MINUS: { //unary minus (example:'-' in "-114514")
            return -prim(true);//return negative value
        }
        case LP: { //handle "()"
            double e = Parser::expr(true);//calculate the formula in this "()"
            if (curr_tok != RP) return error(-1, ") expected");//find couple
            get_token();//eat ')'
            return e;
        }
        default:
            return error(-1, "primary expected");
    }
}


