// 2022 SuperBart, Released under SuperBart Public Domain Software License
// This file is a part of a simulation program.
//  card.hpp
//  Contains serveral class related to a card.

#ifndef _CARD_HPP_
#define _CARD_HPP_
#ifndef _MAGGIE_HPP_
#include "maggie.hpp"
#endif

using namespace maggie;
// Following two should be used as interface.
class insitute
{
private:
    string segood;

public:
    insitute(string _segood) { segood = _segood; };
    const string get_insitute() { return segood; };
};

class pocket
{
private:
    uint money;

public:
    pocket(uint _money) { money = _money; };
    const uint get_money() { return money; };
    void set_money(uint _money) { money += _money; };
    virtual bool pay() = 0;
};

class card
{
private:
    string name;
    bool sex;
    long id;
    unsigned int times;
    int onbus;

public:
    card(string _name, bool _sex, long _id, uint _times)
    {
        name = _name;
        sex = _sex;
        id = _id;
        times = _times;
        onbus = -1;
    }
    // Basic information
    const string get_name() { return name; };
    const bool get_sex() { return sex; };
    long get_id() const { return id; };
    // Times
    const uint get_times() { return times; };
    void set_times(uint add) { times += add; };
    void clear_times() { times = 0; };
    // Is on bus?
    void set_onbus(int a) { onbus = a; };
    void getoff_bus() { onbus = 0; };
    const int get_onbus() { return onbus; };
}; // class card

// Teachers do not need money.
// Input value: name, (bool)sex, id, times, insitute
class teacher : public card, public insitute
{
public:
    teacher(string _name, bool _sex, uint _id, uint _times, string _insitute)
        : card(_name, _sex, _id, _times), insitute(_insitute) {}
    string print()
    {
        stringstream ss;
        ss << get_name() << "\t\t"
           << get_sex() << "\t"
           << get_id() << "\t"
           << get_times() << "\t"
           << get_insitute() << "\t"
           << endl;
        return ss.str();
    }
    bool operator==(const teacher &ps)
    {
        return ps.get_id() == get_id();
    }
}; // class teacher

// Resident does not belong to any insitute.
// Input value: name, (bool)sex, id, money, times
class resident : public card, public pocket
{
public:
    resident(string _name, bool _sex, long _id, uint _money, uint _times)
        : card(_name, _sex, _id, _times), pocket(_money) {}
    string print()
    {
        stringstream ss;
        ss << get_name() << "\t\t"
           << get_sex() << "\t"
           << get_id() << "\t"
           << get_money() << "\t"
           << get_times() << "\t"
           << endl;
        return ss.str();
    }
    bool operator==(const resident &ps)
    {
        return ps.get_id() == get_id();
    }
    bool pay()
    {
        if (get_times() < 20)
        {
            cout << "本次免费乘坐，还剩下" << 20 - get_times() << "次。\n";
            return true;
        }
        else if (get_times() == 20)
        {
            cout << "下次乘坐需要付费。\n";
            return true;
        }

        if (get_money() < TICKET_PRICE)
        {
            cout << "余额不足。\n";
            return false;
        }
        if (get_money() <= 5)
        {
            cout << "请及时续费。\n";
        }
        set_money(-TICKET_PRICE);
        return true;
    }
};

// Students are the worst.
// Input value: name, (bool)sex, id, money, times, insitute
class student : public card, public pocket, public insitute
{
public:
    student(string _name, bool _sex, uint _id, uint _money, uint _times, string _insitute)
        : card(_name, _sex, _id, _times), pocket(_money), insitute(_insitute) {}
    string print()
    {
        stringstream ss;
        ss << get_name() << "\t\t"
           << get_sex() << "\t"
           << get_id() << "\t"
           << get_money() << "\t"
           << get_times() << "\t"
           << get_insitute() << "\t"
           << endl;
        return ss.str();
    }
    bool operator==(const student &ps)
    {
        return ps.get_id() == get_id();
    }
    bool pay()
    {
        if (get_money() < TICKET_PRICE)
        {
            cout << "余额不足。\n";
            return false;
        }
        if (get_money() <= 5)
        {
            cout << "请及时续费。\n";
        }
        set_money(-TICKET_PRICE);
        return true;
    }
};
#endif
