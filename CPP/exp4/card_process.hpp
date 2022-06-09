// 2022 SuperBart, Released under SuperBart Public Domain Software License
// This file is a part of a simulation program.
//  card_process.hpp
//  Something about cards management.
#ifndef _CARD_PROCESS_
#define _CARD_PROCESS_

#include "card.hpp"

using namespace maggie;
struct card_process
{
    // I hate dynamic_cast, too terrible to use in a limited time.
    vector<teacher> teachers;
    vector<student> students;
    vector<resident> residents;
    void add_cards();
    void card_management();
    // teacher.dat student.dat resident.dat
    void read_cardlist();
    void save_cardlist();
    void print_cardlist();
};
#endif
