/* 5.9[13]
 * Define a struct Date to keep track of dates.
 * Provide functions that read Dates from input,
 * write Date es to output,and initialize a Date with a date.
 * 7.10[19]
 * Write functions to add one day, one month, and one year to a Date as defined in §5.9[13].
 * Write a function that gives the day of the week for a given Date.
 * Write a function that gives the Date of the first Monday following a given Date.
 */

#ifndef _DATE_
#define _DATE_

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef _CMATH_
#include <cmath>
#endif

namespace date
{
    using namespace std;
    class Date
    {
    private:
        int m_year;
        int m_month;
        int m_day;
        bool isLeap() const;
        int dayInMonth() const;
        int dayInYear() const;
        int startWeek() const;

    public:
        Date(int year = 1970, int month = 1, int day = 1);
        void print();
        void addDay();
        void addMonth();
        void addYear();
        int evalWeek();
        friend ostream &operator<<(ostream &os, const Date &here);
        void nextWeek();
    };

    inline ostream &operator<<(ostream &os, const Date &here)
    {
        os << here.m_year << "-" << here.m_month << "-" << here.m_day << endl;
        return os;
    }
}

#endif
