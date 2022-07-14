#ifndef _DATE_
#define _DATE_

#ifndef _STRING_
#include <string>
#endif

#ifndef _IOSTREAM_
#include <iostream>
#endif

namespace superbart
{
     using namespace std;
     class Date
     {

     public:
          class Bad_date
          {
          public:
               Bad_date() {}
          }; // exception class

          Date(int yy = 0, int mm = 0, int dd = 0); // 0 means “pick a default”

          // functions for examining the Date

          int day() const;

          int month() const;

          int year() const;

          string string_rep() const; // string representation of the Date, e.g. “2000.2.1”

          void char_rep(char s[]) const; // C-style string representation

          static void set_default(int, int, int);

          // functions for changing the Date

          Date &add_year(int n); // add n years

          Date &add_month(int n); // add n months

          Date &add_day(int n); // add n days

     private:
          int y,
              m,
              d; // year,month,day
          static Date default_date;

          // functions for evaluating the Date

          static bool isvalid(int year, int month, int day);
     };
}

#endif