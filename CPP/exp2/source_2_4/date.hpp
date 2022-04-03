#ifndef _DATE_
#define _DATE_

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _STRING_
#include <string>
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
        bool isLeap()
        {
            if ((m_year % 4 == 0 && m_year % 100 != 0) || m_year % 400 == 0)
                return true;
            else
                return false;
        }
        int dayInMonth(int month)
        {
            bool special = isLeap();
            if (month == 2 && special == true)
                return 29;
            else if (month == 2 && special == false)
                return 28;
            else if (month == 1 || month == 3 || month == 5 ||
                     month == 7 || month == 8 || month == 10 || month == 12)
                return 31;
            else
                return 30;
        }
        int dayInYear()
        {
            return isLeap() ? 366 : 365;
        }

    public:
        Date(int year = 1970, int month = 1, int day = 1);
        void print();
        void addDay();
        void addMonth();
        void addYear();
        int evalWeek();
        void printNextWeek();
    };

    Date::Date(int year, int month, int day)
    {
        m_year = year;
        m_month = month;
        m_day = day;
    }

    void Date::print()
    {
        cout << m_year << " - " << m_month << " - " << m_day << endl;
    }

    void Date::addYear()
    {
        m_year++;
        if (m_day == 29)
            m_day = 28;
        else if (m_day == 28 && isLeap())
            m_day = 29;
    }

    void Date::addMonth()
    {
        /*
         *  1->2    31->29/28
         *  2->3    -
         *  3->4    31->30
         *  4->5    -
         *  5->6    31->30
         *  6->7    -
         *  7->8    -
         *  8->9    31->30
         *  9->10   -
         *  10->11  31->30
         *  11->12  -
         *  12->1   year++
         */
        switch (m_month)
        {
        case 12:
            m_year++;
            m_month = 1;
            break;
        case 1:
            if (isLeap() && m_day > 29)
                m_day = 29;
            else if (m_day > 28)
                m_day = 28;
            m_month++;
            break;
        case 3:
        case 5:
        case 8:
        case 10:
            if (m_day > 30)
                m_day = 30;
            m_month++;
            break;
        default:
            m_month++;
        }
    }

    void Date::addDay()
    {
        m_day++;
        if (m_day > dayInMonth(m_month))
        {
            addMonth();
            m_day = 1;
        }
    }

    // To be implement: eval / getnextweek
}

#endif