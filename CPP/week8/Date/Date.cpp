// Following is an example of incomplete implementation and test
// (Just for reference only). You need to modify it to test other member functions)

#include "Date.h"
#include <cstring>
namespace superbart
{
    using namespace std;
    Date Date::default_date = {1970, 1, 1};

    bool Date::isvalid(int year, int month, int day)
    {
        if (year < 1970)
            return false;
        else if (month < 1 || month > 12)
            return false;
        else if (day < 1 || day > 31)
            return false;
        else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30))
            return false;
        else if (month == 2)
        {
            if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
                return day <= 29;
            else
                return day <= 28;
        }
        else
            return true;
    }

    void Date::set_default(int year, int month, int day)
    {
        default_date.y = year;
        default_date.m = month;
        default_date.d = day;
        if (!isvalid(year, month, day))
            throw Bad_date();
    }

    Date::Date(int yy, int mm, int dd)
    {
        y = yy ? yy : default_date.y;
        m = mm ? mm : default_date.m;
        d = dd ? dd : default_date.d;
        if (!isvalid(y, m, d))
            throw Bad_date();
    }

    string Date::string_rep() const
    {
        return to_string(y) + "." + to_string(m) + "." + to_string(d);
    }

    int Date::day() const
    {
        return d;
    }

    int Date::month() const
    {
        return m;
    }

    int Date::year() const
    {
        return y;
    }

    void Date::char_rep(char s[]) const
    {
        std::strcpy(s, string_rep().c_str());
    }

    Date &Date::add_year(int n)
    {
        y += n;
        // If leap year, check for the 50th day.
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
        {
            if (m == 2 && d == 29)
            {
                m = 3;
                d = 1;
            }
        }
        return *this;
    }

    Date &Date::add_month(int n)
    {
        m += n;
        // If over 12, year + 1
        if (m > 12)
        {
            int count;
            while (m > 12)
            {
                m = m % 12;
                count++;
            }
            y += count;
        }
        return *this;
    }

    Date &Date::add_day(int n)
    {
        d += n;
        // Sorry, I don't want to deal with it.
        if (!isvalid(y, m, d))
        {
            throw Bad_date();
        }
        return *this;
    }
}