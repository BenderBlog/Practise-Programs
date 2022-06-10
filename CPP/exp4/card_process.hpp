/**
 * 2022 SuperBart, this is an absolutely free software released under
 * SuperBart Public Domain Software License.
 * You may gain a copy of this from https://benderblog.github.io/License.html
 *
 * This header file is a part of College ID Card and College Bus Simulation Program.
 *
 * card_process.hpp
 * Description:
 *      Something about cards management.
 *        1. Lists of teacher cards, student cards and resident cards.
 *        2. Card management functions.
 *        3. Store cards into files. Different types store separately.
 *
 */
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
    // teacher.txt student.txt resident.txt
    void read_cardlist();
    void save_cardlist();
    void print_cardlist();
};
#endif
