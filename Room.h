#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "json11.hpp"
#include "Doors.h"
#include "Mob.h"
#include "Object.h"

using json = json11::Json;
using namespace std;

class Room {
private:
    int id;
    string name;
    string description;
    string portal;
    Doors doors;
    vector<int> objects;
    vector<int> mobs;

    bool starting;

    vector<int> getObjectIds();

public:
    Room();
    Room(int minAnum, json jsonRoom);

    int goThroughDoor(string direction, map<string, int> portals);
    int getRoomIdWithPortal(const string& key);
    string getRoomInfo();

    bool isStarting();
    int getRoomId();

    string getExits();
    int getObjectByName(map<int, Object> allObjects, string name);
    string getObjectInfo(map<int, Object>);
    void removeObject(int objId);
    void addObjectToRoom(int objId);
    string getMobInfo(map<int, Mob> mobData);
    int getMob();
    void removeMob(int mobId);

    friend std::ostream& operator<<(std::ostream& os, const Room& room);

};

#endif // ROOM_H
