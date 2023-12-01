#ifndef WORLD_H
#define WORLD_H

#include <map>
#include "Room.h"
#include "Object.h"
#include "Player.h"
#include "json11.hpp"
#include "Mob.h"

using namespace std;
using json = json11::Json;

class World {
private:
    std::map<int, Room> rooms;
    std::map<int, Object> objects;
    std::map<int, Mob> mobs;
    std::map<string, int> portals;
    int startingRoom = -1;
    int findRoomIdByPortal(string key);
    void addPortal(const string& from, string to, bool twoway);
    void addRoom(Room *room);
    void addMob(Mob *mob);
    void addObject(Object *room);
    void removeMob(int roomId, int mobId);
    Mob getMob(int roomId);

public:
    explicit World();

    bool move(Player *player, string direction);

    void addRooms(int minVnum, const json &jsonRooms);
    void addMobs(int minAnum, const json &jsonMobs);
    void addPortals(const json&  jsonPortals);
    void addObjects(int minAnum, const json &jsonRooms);

    int getStartingLocation() const;
    string getRoomInfo(int roomId);

    string look(int roomId, string item);
    string pickupObjectByName(Player *player, string itemName);
    string dropObject(Player *player, int indexId);
    string getObjectNames(const vector<int>& inventoryItems);
    void performAttack(Player *player);


};


#endif // WORLD_H
