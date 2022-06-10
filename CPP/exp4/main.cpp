/**
 * 2022 SuperBart, this is an absolutely free software released under
 * SuperBart Public Domain Software License.
 * You may gain a copy of this from https://benderblog.github.io/License.html
 *
 * This header file is a part of College ID Card and College Bus Simulation Program.
 *
 * card_process.cpp
 * Description:
 *      Main formula including a pretty dumb simulation program.
 *
 */
#include "bus.hpp"
#include "card.hpp"
#include "card_process.hpp"
#include "bus_process.hpp"

using namespace maggie;

bus_process buses;
card_process cards;

// Dumb Simulation Program
int simulation()
{
    cout << "====模拟开始====" << endl;
    // 随意设定离站时间
    random_device seed;              // Used for generate seed for random number generator
    default_random_engine e{seed()}; // Random number generator
    for (auto i = buses.station.begin(); i < buses.station.end(); ++i)
    {
        uniform_int_distribution<uint> u(8, 17);
        (*i).set_offtime(u(e));
        cout << (*i).get_driver() << "的班车离站时间设定为" << (*i).get_offtime() << "点\n";
    }
    cout << "\n现在开始模拟\n";
    // 班车运行时间是九点到十八点
    for (int clk = 6; clk < 19; ++clk)
    {
        cout << "目前时间是" << clk << "点\n";
        // 侦测进站班车
        for (auto i = buses.ongoing.begin(); i < buses.ongoing.end(); ++i)
        {
            if ((*i).get_offtime() == clk - RUN_TIME)
            {
                cout << (*i).get_driver() << "的班车要到站\n";
                buses.station.push_back((*i));
                (*i).clear();
                buses.ongoing.erase(i);
            }
        }
        // 侦测离站班车
        for (auto i = buses.station.begin(); i < buses.station.end(); ++i)
        {
            if ((*i).get_offtime() == clk)
            {
                cout << (*i).get_driver() << "的班车要离站\n";
                // 随便来点十七号城市的难民
                uniform_int_distribution<uint> u(0, (*i).get_max());
                (*i).set_onboard_count(u(e));
                // 然后再加点人
                if ((*i).isfull())
                {
                    cout << "车满了，不摇人了。\n";
                }
                else
                {
                    cout << "车上了" << (*i).get_onboard_count() << "人，摇人。\n";
                    // 随便拉个人上车
                    uniform_int_distribution<uint> u2(0, 2);
                    // 抽中个老师
                    if (u2(e) == 0 && cards.teachers.size() > 0)
                    {
                        uniform_int_distribution<uint> u3(0, cards.teachers.size() - 1);
                        teacher &to_deal = cards.teachers[u3(e)];
                        if (to_deal.get_onbus() != -1)
                        {
                            cout << to_deal.get_name() << "老师上车了。\n";
                        }
                        else if ((*i).onboard(to_deal.get_id()))
                        {
                            to_deal.set_times(1);
                            cout << "班车" << (*i).get_id() << "上了" << to_deal.get_name() << "老师\n";
                        }
                        else
                        {
                            cout << "怪事，这老师能上车的呢。" << endl;
                        }
                    }
                    // 抽中个学生
                    else if (u2(e) == 1 && cards.students.size() > 0)
                    {
                        uniform_int_distribution<uint> u3(0, cards.students.size() - 1);
                        student &to_deal = cards.students[u3(e)];
                        if (to_deal.get_onbus() != -1)
                        {
                            cout << to_deal.get_name() << "学生上车了。\n";
                        }
                        else if (to_deal.pay())
                        {
                            if ((*i).onboard(to_deal.get_id()))
                            {
                                to_deal.set_times(1);
                                cout << "班车" << (*i).get_id() << "上了" << to_deal.get_name() << "学生\n";
                            }
                        }
                        else
                        {
                            cout << "这同志没钱了。\n";
                        }
                    }
                    // 抽中个住户
                    else if (u2(e) == 2 && cards.residents.size() > 0)
                    {
                        uniform_int_distribution<uint> u3(0, cards.residents.size() - 1);
                        resident &to_deal = cards.residents[u3(e)];
                        if (to_deal.get_onbus() != -1)
                        {
                            cout << to_deal.get_name() << "家属上车了。\n";
                        }
                        else if (to_deal.pay())
                        {
                            if ((*i).onboard(to_deal.get_id()))
                            {
                                to_deal.set_times(1);
                                cout << "班车" << (*i).get_id() << "上了家属，其名字为" << to_deal.get_name() << "\n";
                            }
                        }
                        else
                        {
                            cout << "这同志没法乘车。\n";
                        }
                    }
                    // 没找到就算了
                    else
                    {
                        cout << "我不想抽了，如果我的人生只有 Maggie 那该多好啊。\n";
                    }
                }
                // 出发！
                buses.ongoing.push_back((*i));
                (*i).clear();
                buses.station.erase(i);
            }
        }

        cout << "正在车站的车有：\n";
        buses.list_bus(buses.station);
        cout << "正在运行的车有：\n";
        buses.list_bus(buses.ongoing);
        cout << endl;
    }
    cout << "模拟结束，上车人数和时刻表全部瞎编，2333。\n";
    return 0;
}

int main()
{
    cards.read_cardlist();
    buses.read_station();
    uint choose;
    cout << "1.管理班车\n2.管理卡\n3.运行模拟\n0.退出\n";
    while (cin >> choose)
    {
        switch (choose)
        {
        case 1:
            buses.bus_management();
            break;
        case 2:
            cards.card_management();
            break;
        case 3:
            simulation();
            break;
        case 0:
            cards.save_cardlist();
            buses.save_station();
            return 0;
        default:
            cout << "输入错误，请重新输入\n";
            break;
        }
        cout << "1.管理班车\n2.管理卡\n3.运行模拟\n0.退出\n";
    }
}
