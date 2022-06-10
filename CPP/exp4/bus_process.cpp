/**
 * 2022 SuperBart, this is an absolutely free software released under
 * SuperBart Public Domain Software License.
 * You may gain a copy of this from https://benderblog.github.io/License.html
 *
 * This header file is a part of College ID Card and College Bus Simulation Program.
 *
 * bus_process.cpp
 * Description:
 *      Implemention of bus_process.hpp. I think code them separately is better.
 *
 */

#include "bus_process.hpp"
using namespace maggie;

void bus_process::add_bus()
{
    uint b_num, b_size;
    string b_driver;
    cout << "新建班车信息\n依次输入驾驶员姓名、编号、载乘人(30或50)\n";
    cout << "输入“0 0 0”退出新建班车\n";
    while (cin >> b_driver >> b_num >> b_size && b_num != 0)
    {
        bool isbig = false;
        if (b_size == 50)
            isbig = true;
        bus toappend(b_driver, b_num, isbig);
        station.push_back(toappend);
    }
}

void bus_process::bus_management()
{
    uint choose;
    cout << "1. 新建班车\n2. 查看班车\n0. 退出\n";
    while (cin >> choose)
    {
        switch (choose)
        {
        case 1:
            add_bus();
            break;
        case 2:
            list_bus(station);
            break;
        case 0:
            return;
        default:
            cout << "输入错误，请重新输入\n";
            break;
        }
        cout << "1. 新建班车\n2. 查看班车\n0. 退出\n";
    }
}

void bus_process::list_bus(vector<bus> &list)
{
    for (auto &i : list)
    {
        cout << i.print();
    }
}

void bus_process::read_station()
{
    cout << "Reading bus...\n";
    ifstream fin("bus.txt");
    if (!fin)
    {
        cout << "文件打开失败\n";
        return;
    }
    string b_driver;
    uint b_id;
    bool b_model;
    while (fin >> b_driver >> b_id >> b_model)
    {
        bus toappend(b_driver, b_id, b_model);
        station.push_back(toappend);
    }
    fin.close();
}

void bus_process::save_station()
{
    cout << "Saving station.\n";
    ofstream fout("bus.txt");
    if (!fout)
    {
        cout << "文件打开失败\n";
        return;
    }
    for (auto &i : station)
    {
        fout << i.print();
    }
    fout.close();
}
