/**
 * 2022 SuperBart, this is an absolutely free software released under
 * SuperBart Public Domain Software License.
 * You may gain a copy of this from https://benderblog.github.io/License.html
 *
 * This header file is a part of College ID Card and College Bus Simulation Program.
 *
 * bus.hpp
 * Description:
 *      A College Bus class. I believe I have written all the information clearly.
 *
 */

#ifndef _BUS_
#define _BUS_
#ifndef _MAGGIE_HPP_
#include "maggie.hpp"
#endif

using namespace maggie;

class bus
{
private:
    string driver;      // driver's name
    uint id;            // bus's id
    bool model;         // bus's model, if ture, it's a big bus, otherwise, it's a small bus.
    uint onboard_id;    // the person who on the bus
    uint offtime;       // the time when the bus is off
    uint onboard_count; // the number of people on the bus

public:
    // driver, id, model
    bus(string _driver, uint _id, bool _model)
    {
        driver = _driver;
        id = _id;
        model = _model;
        onboard_id = 0;
        offtime = 0;
        onboard_count = 0;
    }
    // basic bus information
    string get_driver() const { return driver; }
    uint get_id() const { return id; };
    uint get_max() const { return model ? 50 : 30; }
    string print()
    {
        stringstream ss;
        ss << driver << "\t" << id << "\t" << model << endl;
        return ss.str();
    }
    // people get on the bus
    bool onboard(uint id_card)
    {
        if (onboard_count >= get_max())
        {
            cout << "公交车满员了。\n";
            return false;
        }
        onboard_id = id_card;
        onboard_count++;
        return true;
    }

    // clear the bus
    void clear()
    {
        onboard_id = 0;
        onboard_count = 0;
    }
    // about offtime
    uint get_offtime() const { return offtime; };
    void set_offtime(uint _offtime) { offtime = _offtime; }
    // about max onboard and onboard count
    bool isfull() const { return onboard_count >= get_max(); }
    void set_onboard_count(uint i) { onboard_count = i; }
    uint get_onboard_count() const { return onboard_count; }
};
#endif
