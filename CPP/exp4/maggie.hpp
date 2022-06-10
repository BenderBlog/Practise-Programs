/**
 * 2022 SuperBart, this is an absolutely free software released under
 * SuperBart Public Domain Software License.
 * You may gain a copy of this from https://benderblog.github.io/License.html
 *
 * This header file is a part of College ID Card and College Bus Simulation Program.
 *
 * maggie.hpp
 * Description: Everything in this software is in the maggie namespace,
 *              which includes std namespace as well as some variables.
 */

#ifndef _MAGGIE_HPP_
#define _MAGGIE_HPP_
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <ctime>
#include <unistd.h>
#include <random>
#include <cstring>
namespace maggie
{
    using namespace std;
    const uint TICKET_PRICE = 2;    // How much is a bus ticket.
    const uint RUN_TIME = 1;        // How long has the bus runs.
    const uint BUS_MAX_SIZE = 50;   // Small bus.
    const uint BUS_MIN_SIZE = 30;   // Bug bus.
}
#endif
