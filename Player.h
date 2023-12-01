//
// Created by etrickel on 10/20/2023.
//

#ifndef CPPMUD_PLAYER_H
#define CPPMUD_PLAYER_H
#include <vector>

using namespace std;

class Player {

    int location =0;

    vector<int> inventory;
    int hitpoints=999;
    string hitdice="1d12+2000";


public:
    Player();

    int getLocation();
    void setLocation(int newLocation);
    void addToInventory(int objId);

    vector<int> getInventory();

    int removeObjectFromInventory(int indexToRemove);
    bool hasItems();
    int getHitpoints();
    int rollForAttack();
    void teleport(int loc);
};


#endif //CPPMUD_PLAYER_H
