#include <iostream>
#include <cstdarg>
#include <string>
using namespace std;

void error(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    string toOutput = format;
    for (int i = 0; i < toOutput.size(); ++i)
    {
        if (toOutput[i] == '%')
        {
            i++;
            if (toOutput[i] == '%')
            {
                cout << '%';
            }
            else if (toOutput[i] == 's')
            {
                string a = va_arg(ap, const char *);
                cout << a;
            }
            else
            {
                int a = va_arg(ap, int);
                if (toOutput[i] == 'c')
                {
                    cout << (char)a;
                }
                else if (toOutput[i] == 'd')
                {
                    cout << a;
                }
            }
        }
        else
        {
            cout << toOutput[i];
        }
    }
    va_end(ap);
}

int main()
{
    error("Hello %s, %d, %c. %%\n", "SuperBart", 'f', 'f');
    // For test.
    printf("Hello %s, %d, %c. %%\n", "SuperBart", 'f', 'f');
}