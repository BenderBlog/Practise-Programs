#include<iostream>
#include<string>
#include<ctime>
using namespace std;

char const * calender[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

int main(){
    struct Date{
        int year;
        string month;
        int day;
    };
    Date output;
    // Input string, like 2022-02-21.
    string input;
    cin >> input;
    output = {
                stoi(input.substr(0,4)),
                calender[stoi(input.substr(5,1)) + 1],
                stoi(input.substr(8,2)) 
            };
    cout << "Year: " << output.year << ", Month: " << output.month << ", Day: " << output.day << endl;
}

/*
// Using an array of char for the name, and an array for the number of days.
char * month[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
int day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
// Using an array of structures, with each structure holding the name of a month and the number of days in it.
struct Date{
    char * month;
    int day;
};
Date together[12] = {
                        {"Jan",31},
                        {"Feb",28},
                        {"Mar",31},
                        {"Apr",30},
                        {"May",31},
                        {"Jun",30},
                        {"Jul",31},
                        {"Aug",31},
                        {"Sep",30},
                        {"Oct",31},
                        {"Nov",30},
                        {"Dec",31}
                    };
*/
