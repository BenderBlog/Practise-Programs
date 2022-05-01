#include "Date.h"

using namespace superbart;

int main()
{
    try
    {
        Date d1;
        cout << d1.year() << "-" << d1.month() << "-" << d1.day() << endl;
        Date d2(2022, 4, 17);
        cout << d2.string_rep() << endl;
        Date::set_default(2001, 2, 29);
        Date d3;
        cout << d3.string_rep() << endl;
    }
    catch (Date::Bad_date)
    {
        cout << "A bad date!\n"
             << endl;
    }

    return 0;
}
