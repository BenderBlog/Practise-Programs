/*
    2021 SuperBart, relesed under SuperBart Public Domain Software License.
    Question:
        Read a sequence of possibly whitespace-separated (name,value) pairs,
        where the name is a single whitespace-separated word and the value is
        an integer or a floating-point value. Compute and print the sum and
        mean for each name and the sum and mean for all names.
*/

#include <string>
#include <map>
#include <iostream>

using namespace std;

struct whatdata
{
    int count;
    double total;
    whatdata()
    {
        count = 0;
        total = 0;
    }
    whatdata(int c, double t)
    {
        count = c;
        total = t;
    }
};

int main()
{
    map<string, whatdata> dict;
    int count;
    int total = 0;
    int times = 0;

    cin >> count;
    for (int i = 0; i < count; ++i)
    {
        string name;
        double value;
        cin >> name >> value;
        if (dict.find(name) == dict.end())
        {
            dict[name] = whatdata(1, value);
        }
        else
        {
            dict[name].count++;
            dict[name].total += value;
        }
    }
    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
        cout << it->first << " " << it->second.count << " " << it->second.total << " " << it->second.total / it->second.count << endl;
        total += it->second.total;
        times += it->second.count;
    }
    cout << "Total: " << total << " Avg: " << total / times << endl;
    return 0;
}
