// 2022 SuperBart, Released under SuperBart Public Domain Software License
// This file is a part of a simulation program.
//  bus_process.hpp
//  Something about buses management.

#ifndef _BUS_PROCESS_
#define _BUS_PROCESS_

#include "bus.hpp"
using namespace maggie;
class bus_process
{
public:
    vector<bus> station;
    vector<bus> ongoing;
    void add_bus();
    void list_bus(vector<bus> &);
    void bus_management();
    void read_station();
    void save_station();
};

#endif
