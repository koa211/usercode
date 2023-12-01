#include "World.h"
#include <vector>
#include <iostream>
#include <sstream>

/**
 * Basic constructor for world
 */
World::World()= default;

/**
 * Searches through all the rooms to find the roomId with the portal name either in its room.portal or its doors
 * @param portalName
 * @return roomId or -1
 */
int World::findRoomIdByPortal(string portalName){
    cout << "World::findRoomIdByPortal placeholder " << portalName << endl;

    return -1;
}

void World::addPortals(const json& jsonPortals){
    //cout << "World::addPortals placeholder " << jsonPortals.dump() << endl;
    for (auto port : jsonPortals.array_items()) {
        json jp = port["portal"];
        cout << jp["from"].string_value() << endl;
        //rooms.find
    }
}

/**
 * Discovers the to and from roomId's for the portals and stores them in World's portal
 * If twoway is true then it reverses the from and to and stores that as well
 * @param from
 * @param to
 * @param twoway
 */
void World::addPortal(const string& from, string to, bool twoway){
    cout << "World::addPortal placeholder " << from <<  " " << to << " " << twoway << endl;
}


/**
 * Adds all the rooms of an area (e.g., Midgaard) to the world according to their modified roomId (minAnum + room anum)
 * using Room constructor and World::addRoom
 * @param minAnum
 * @param jsonRooms
 */
void World::addRooms(int minVnum, const json &jsonRooms){
    //part of what was printing out
    //cout << "World::addRooms placeholder " << minVnum <<  " " << jsonRooms.dump() << endl;

    //loop through all rooms coming in a json format
    for (auto entry : jsonRooms.array_items()) {
        Room *room = new Room(minVnum, entry["room"]);
        cout << room->getRoomId() << endl;
        addRoom(room);
        if (room->isStarting()) {
            startingRoom = room->getRoomId();
        }
    }
}


/**
 * Add a room to World::rooms map.
 * @param room
 */
void World::addRoom(Room *room) {
    //cout << "World::addRoom placeholder " << room->getRoomId() << endl;
    //map of rooms

    rooms[room->getRoomId()] = *room; 
}

/**
 * Adds all the objects of an area (e.g., Midgaard) to the world according to their modified objectId (minAnum + object anum)
 * using the Object constructor and World::addObject
 * @param minAnum
 * @param jsonRooms
 */
void World::addObjects(int minAnum, const json &jsonRooms){
    cout << "World::addObjects placeholder " << minAnum <<  " " << jsonRooms.dump() << endl;
}

/**
 * Adds an object to the World's map of objects
 * @param object
 */
void World::addObject(Object *object) {
    cout << "World::addObject placeholder " << object->getObjectInfo() << endl;
}

/**
 * Adds all the Mobs of an area (e.g., Midgaard) to the world according to the modified mobId (minAnum + mob anum)
 * using the Mob constructor and World::addMob
 * @param minAnum
 * @param jsonMobs
 */
void World::addMobs(int minAnum, const json &jsonMobs){
    cout << "World::addMobs placeholder " << minAnum <<  " " << jsonMobs.dump() << endl;
}

/**
 * Add the mob object to World::mobs
 * @param mob
 */
void World::addMob(Mob *mob) {
    cout << "World::addMob placeholder " << mob->getName() << endl;
}

/**
 * Moves the player in a direction if the direction is available. The direction is a string direction that can be
 * any portion of north, south, east, west, up, down
 * @param player
 * @param direction
 * @return
 */
bool World::move(Player *player, string direction){
    cout << "World::move placeholder " << player->getHitpoints() <<  direction << endl;
    return false;
}

/**
 * Gets the starting location of the world
 * @return
 */
int World::getStartingLocation() const {
    return startingRoom;
}

/**
 * Generates information for a room including basic room info, ID, room name, room description, room objects,
 * mob info, and exits. It returns all of this information as a string
 * @param roomId
 * @return
 */
string World::getRoomInfo(int roomId){
    ostringstream infoStream;
    infoStream << rooms[roomId].getRoomInfo();
    // Can use infoStream like this to concatenate strings
    // this is a placeholder
    //infoStream << roomId << endl;

    return infoStream.str();
}

/**
 * From within a room, look at an item with the provided name and return the item description.
 * @param roomId
 * @param item
 * @return the object's description
 */
string World::look(int roomId, string item){
    cout << "World::look placeholder " << roomId <<  item << endl;
    return "";
}

/**
 * Given the player's location, pickup the item and place it into the player's inventory
 * @param player
 * @param itemName
 * @return the name of the item that was picked up
 */
string World::pickupObjectByName(Player *player, string itemName){
    cout << "World::pickupObjectByName placeholder " << player->getHitpoints() <<  itemName << endl;
    return "";
}

/**
 * Given the player's location, drop the item with the provided indexId and place it on the floor in the current room.
 * @param player
 * @param indexId
 * @return the object's name
 */
string World::dropObject(Player *player, int indexId){
    cout << "World::dropObject placeholder " << player <<  " " << indexId << endl;
    return "";
}

/**
 * Given a vector of Object ids it will return the list of inventory items using an index
 * @param inventoryItems
 * @return
 */
string World::getObjectNames(const vector<int>& inventoryItems) {
    ostringstream infoStream;
    cout << "World::getObjectNames placeholder " << inventoryItems.at(0)  << endl;

    return infoStream.str();
}

/**
 * Get the first mob in a room
 * @param roomId
 * @return Mob object
 */
Mob World::getMob(int roomId){
    cout << "World::getMob placeholder " << roomId << endl;
    return Mob(); // default return when not found
}

/**
 * Remove a mob with the mobId from the room and update the room in the rooms map.
 * @param roomId
 * @param mobId
 */
void World::removeMob(int roomId, int mobId){
    cout << "World::removeMob placeholder " << roomId <<  " " << mobId << endl;
}

/**
 * The sequence of actions where a player attacks a mob and the mob attacks the player until one of the dies
 * On death of the mob, the mob is removed from the world the player is notified "You win, you have killed the "
 * On death of the player, the player is notified "You Died! You have been killed by"
 * As this gets more complicated, it should be extracted into its own class
 * @param player
 */
void World::performAttack(Player *player) {
    cout << "World::performAttack placeholder " << player->getHitpoints() << endl;
}