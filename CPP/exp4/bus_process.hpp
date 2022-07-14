/**
 * 2022 SuperBart, this is an absolutely free software released under
 * SuperBart Public Domain Software License.
 * You may gain a copy of this from https://benderblog.github.io/License.html
 *
 * This header file is a part of College ID Card and College Bus Simulation Program.
 *
 * bus_process.hpp
 * Description:
 *      Something about cards management.
 *        1. Hire a new driver and buy a new bus.
 *        2. Good management, we don't need to sell them 233.
 *
 */

#ifndef _BUS_PROCESS_
#define _BUS_PROCESS_

#include "bus.hpp"
using namespace maggie;
struct bus_process
{
    vector<bus> station;
    vector<bus> ongoing;
    void add_bus();
    void list_bus(vector<bus> &);
    void bus_management();
    void read_station();
    void save_station();
};

#endif
