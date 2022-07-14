/**
 * 2022 SuperBart, this is an absolutely free software released under
 * SuperBart Public Domain Software License.
 * You may gain a copy of this from https://benderblog.github.io/License.html
 *
 * This header file is a part of College ID Card and College Bus Simulation Program.
 *
 * card.hpp
 * Description:
 *      A College ID Card have three elements:
 *        1. Basic information: every card needs this, contains name, id, etc.
 *        2. Insitute information: resident does not need this.
 *        3. Pocket information: actually wallet, teacher does not need this.
 *      You may get three kinds of cards from these elements. Student got them all.
 *
 */

#ifndef _CARD_HPP_
#define _CARD_HPP_
#ifndef _MAGGIE_HPP_
#include "maggie.hpp"
#endif

using namespace maggie;

// Following two class should be used as interface.
class insitute
{
private:
    string segood;

public:
    insitute(string _segood) { segood = _segood; };
    const string get_insitute() const { return segood; };
};

// Actually "wallet" is more proper 233
class pocket
{
private:
    uint money;

public:
    pocket(uint _money) { money = _money; };
    uint get_money() const { return money; };
    // Charge your pocket.
    void set_money(uint _money) { money += _money; };
    // Pay for the ticket.
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
    string get_name() const { return name; };
    bool get_sex() const { return sex; };
    long get_id() const { return id; };
    // Times
    uint get_times() const { return times; };
    void set_times(uint add) { times += add; };
    void clear_times() { times = 0; };
    // Is on bus?
    void set_onbus(int a) { onbus = a; };
    void getoff_bus() { onbus = 0; };
    int get_onbus() const { return onbus; };
    // Print
    virtual string print() = 0;
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
    // For find() formula from stl algorithm.
    bool operator==(const teacher &ps)
    {
        return ps.get_id() == get_id();
    }
};

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
