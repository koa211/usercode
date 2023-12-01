//
// Created by etrickel on 10/21/2023.
//

#ifndef CPPMUD_MOB_H
#define CPPMUD_MOB_H

#include <string>
#include "json11.hpp"

using namespace std;
using json = json11::Json;

class Mob {
    string name;
    string description="";

    int level=-1;
    string hit_dice;
    string damage_dice;
    int id=-1;

public:
    Mob();
    Mob(int anumMin, json mobData);

    string getName();
    int getMobId();
    int rollForHitPoints();
    int rollForAttack();
};


#endif //CPPMUD_MOB_H
