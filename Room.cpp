#include "Room.h"
#include <stdio.h>
#include <sstream>


using namespace std;
/**
 * Overrides the << operator so that we can print out a room's information using just cout << *room;
 * good for debugging
 * Mostly for debugging
 * @param os
 * @param room
 * @return
 */
ostream& operator<<(ostream& os, const Room& room) {
    os << "Room ID: " << room.id << endl;
    os << "Name: " << room.name << endl;
    os << "Description: " << room.description << endl;
    os << "Doors: " << room.doors << endl;
    os << endl;
    /*os << "Object ID: " << room.object << endl;*/
    os << "Starting: " << (room.starting ? "true" : "false") << endl;
    return os;
}
/**
 * Default constructor for a room
 */
Room::Room(){
    id = -1;
    name="";
    description="";
};
/**
 * Load room information using the provided JSON data make sure to check for is_null() and use empty values in the
 * strings instead. Refer to requirements regarding the craziness possible with the "resets" information
 * [
    {"room": {
        "area": "midgaard",
        "anum": 1,
        "name": "The Temple Of Mota",
        "description": ".\n",
         ....
        "portal": "midgaard-5",
        "doors": [ { "dir": "north", "to": 54,"portal": null },  { "dir": "up", "to": null, "portal": "midgaard-6-up" ... } ],
        "resets": [ { "command": "mobile", "values": { "mob": 11 ... } }, { "command": "equip", "values": { "obj": 5 ... } } ]
         } },  ... ]

 * @param minAnum
 * @param jsonRoom
 */
Room::Room(int minAnum, json jsonRoom) {

    int anum = jsonRoom["anum"].int_value();
    id = anum  + minAnum;
    starting = (id == 3001); // if room id == 3001 then it's the starting room
    if (jsonRoom["name"].is_null()) {
        name = "";
    } else {
        name = jsonRoom["name"].string_value();
    }
    if (jsonRoom["description"].is_null()) {
        description = "";
    } else {
        description = jsonRoom["description"].string_value();
    }
    if (jsonRoom["portal"].is_null()) {
        portal = "";
    } else {
        portal = jsonRoom["portal"].string_value();
    }
    //doors
    if (!jsonRoom["doors"].is_null()) {
        // door values are going in -- cout << "room:room door: " << jsonRoom["doors"].array_items()[0]["dir"].string_value() << endl;
        doors.loadJson(minAnum, jsonRoom["doors"]);
    }
    //resets, equipment and mobs
}

/**
 * Travel through a door in a particular direction
 * @param direction
 * @param portals
 * @return the unique roomId of the destination room
 */
int Room::goThroughDoor(string direction, map<string, int> portals){

    return doors.goThroughDoor(direction, portals);

}

/**
 * Get Id of the room with the portal name, check if at room level portal or door/direction portal
 * @param key
 * @return integer id of room with portal or -1
 */
int Room::getRoomIdWithPortal(const string& portalName){
        cout << "Room::getRoomIdWithPortal placeholder " << portalName << endl;
    return -1;
}

/**
 * Return the directions with available exits from this room.
 * @return
 */
string Room::getExits(){
    return doors.getExits();
}

/**
 * Return the object ids that are currently existing in the room.
 * @return the object ids
 */
vector<int> Room::getObjectIds(){
    return objects;
}

/**
 * Remove an object from the room
 * @param objId
 */
void Room::removeObject(int objId){
    cout << "Room::addObjectToRoom placeholder " << objId << endl;
}

/**
 * Place an object with the provided object Id in the room
 * @param objId
 */
void Room::addObjectToRoom(int objId){
    cout << "Room::addObjectToRoom placeholder " << objId << endl;
}

/**
 * Get info on all the objects residing in the room.
 * For multiple objects make sure the commas are in the correct place
 * @param allObjects
 * @return
 */
string Room::getObjectInfo(map<int, Object> allObjects){
    ostringstream infoStream;
    infoStream << "Room::addObjectToRoom placeholder " << allObjects.at(0) << endl;
    return infoStream.str();
}


/**
 * Get information about the room including id, name description returned
 * @return a string containing the information
 */
string Room::getRoomInfo(){
    ostringstream infoStream;

    infoStream << "#" << id << " " << name << endl;

    infoStream << "" << description;

    if (description.back() != '\n'){
        infoStream << endl;
    }
    
    cout << doors << endl;
    return infoStream.str();
}

/**
 * Get the Id of an Object that resides in the current room and matches the provided itemName
 * The match can be a substring of the Object name but must match the entire itemName
 * Example: if itemName == "sci" and their is a scimitar in the room, it will return the scimatar's id
 *          if multiple objects in the room match, it will return the first one matched
 * @param allObjects
 * @param itemName
 * @return
 */
int Room::getObjectByName(map<int, Object> allObjects, string itemName){
    cout << "Room::addObjectToRoom placeholder " << itemName << allObjects.at(0) << endl;
    return -1;
}

/**
 * Gather information on the mob and return that information, might consider colorizing to stand out
 * The ansi escape sequence "\033[38;5;12m" is nice
 * Example: "\033[38;5;12mUnicorn"\033[0m"
 * @param mobData
 * @return a string containing each of the Mobs that reside inside this room.
 */
string Room::getMobInfo(map<int, Mob> mobData){
    ostringstream infoStream;
    cout << "Room::getMobInfo placeholder " << mobData.at(0).getName() << endl;
    return infoStream.str();

}

/**
 * Gets the Mob Id for the first available monster in the room. If no mob then return -1
 * @return mob Id
 */
int Room::getMob(){
    return -1;
}

/**
 * Removes the mobId from the vector of mob ids that represents the mobs residing in this room.
 * Make sure you only remove a single mob with that ID if multiple exist in the room.
 */
void Room::removeMob(int mobId){
    cout << "Room::removeMob placeholder " << mobId << endl;
}

/**
 * Returns whether this room is the player's starting room
 * @return boolean
 */
bool Room::isStarting(){
    return starting;
}

/**
 * Getter for room id
 * @return integer room id
 */
int Room::getRoomId(){
    return id;
}