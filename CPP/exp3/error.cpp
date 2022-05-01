#include "error.h"

using namespace Error;

int Error::no_of_errors = 0;

double Error::error(int n, const string &str)
{
    no_of_errors ++;
    cerr << "Error: " << str << endl;
    return 1;
}
