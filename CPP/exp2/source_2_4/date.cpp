#include "date.hpp"

using namespace date;

bool Date::isLeap() const
{
    if ((m_year % 4 == 0 && m_year % 100 != 0) || m_year % 400 == 0)
        return true;
    else
        return false;
}
int Date::dayInMonth() const
{
    if (m_month == 2 && isLeap())
        return 29;
    else if (m_month == 2 && !isLeap())
        return 28;
    else if (m_month == 1 || m_month == 3 || m_month == 5 ||
             m_month == 7 || m_month == 8 || m_month == 10 || m_month == 12)
        return 31;
    else
        return 30;
}

int Date::dayInYear() const
{
    return isLeap() ? 366 : 365;
}
int Date::startWeek() const
{
    int levelWeek = 5, totalDay = 0; // The standard is 2021-1-1 Friday
    if (m_year - 2021 <= 0)
    {
        for (int i = m_year; i < 2021; ++i)
        {
            if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
            {
                totalDay += 366;
            }
            else
            {
                totalDay += 365;
            }
        }
        return abs(levelWeek - totalDay % 7);
    }
    else
    {
        for (int i = m_year - 1; i > 2021; --i)
        {
            if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
            {
                totalDay += 366;
            }
            else
            {
                totalDay += 365;
            }
            // cout << "totalday: " << totalDay << endl;
        }
        // cout << "After %7: " << totalDay % 7 << endl;
        // cout << "Startweek of : " << m_year << " " << abs(levelWeek + totalDay % 7) % 7 + 1 << endl;
        int toReturn = abs(levelWeek + totalDay % 7) % 7 + 1;
        return toReturn == 7 ? 0 : toReturn;
    }
}

Date::Date(int year, int month, int day)
{
    m_year = year;
    m_month = month;
    m_day = day;
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
    if (m_day > dayInMonth())
    {
        m_day = 1;
        addMonth();
    }
}

int Date::evalWeek()
{
    int count = startWeek() - 1;
    // cout << count << endl;
    for (int currentMonth = 1; currentMonth < m_month; ++currentMonth)
    {
        if (currentMonth == 2 && isLeap())
            count += 29;
        else if (currentMonth == 2 && !isLeap())
            count += 28;
        else if (currentMonth == 1 || currentMonth == 3 || currentMonth == 5 ||
                 currentMonth == 7 || currentMonth == 8 || currentMonth == 10 || currentMonth == 12)
            count += 31;
        else
            count += 30;
        // cout << count << endl;
    }
    // cout << (count + m_day) << endl;
    return (count + m_day) % 7;
}

void Date::nextWeek()
{
    addDay();
    while (evalWeek() != 1)
    {
        addDay();
    }
}

int main()
{
    Date a(2019, 12, 23);
    cout << a.evalWeek() << " " << a;
    a.nextWeek();
    cout << a.evalWeek() << " " << a;
    a.addDay();
    cout << a.evalWeek() << " " << a;
    a.addMonth();
    cout << a.evalWeek() << " " << a;
    a.addMonth();
    cout << a.evalWeek() << " " << a;
    a.addYear();
    cout << a.evalWeek() << " " << a;
    a.nextWeek();
    cout << a.evalWeek() << " " << a;
    Date b(2022, 12, 23);
    cout << b.evalWeek() << " " << b;
    b.nextWeek();
    cout << b.evalWeek() << " " << b;
    b.addDay();
    cout << b.evalWeek() << " " << b;
    b.addMonth();
    cout << b.evalWeek() << " " << b;
    b.addMonth();
    cout << b.evalWeek() << " " << b;
    b.addYear();
    cout << b.evalWeek() << " " << b;
    b.nextWeek();
    cout << b.evalWeek() << " " << b;
}