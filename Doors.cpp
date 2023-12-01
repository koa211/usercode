#include "Doors.h"
#include <sstream>

/**
 * Direction constructor that expects int to and a string value of the remote location
 * @param to
 * @param remoteLocation
 */
Direction::Direction(int to, string remoteLocation) : to(to), remoteLocation(remoteLocation){}

/**
 * A default constructor for Doors
 */
Doors::Doors(){}

/**
 * Get a string containing the letter of a direction n,s,e,w,u,d
 * @param strDirection
 * @return
 */
string getDirLetter(string strDirection){
    //cout << "placeholder for compilation " << strDirection << endl;
    //return string of first letter and make it lowercase
    string dirLetter = strDirection.substr(0,1);
    dirLetter[0] = tolower(dirLetter[0]);
    return dirLetter;
    return ""; //??
}

/**
 * Override << to print out the doors
 * @param os
 * @param doors
 * @return
 */
std::ostream& operator<<(std::ostream& os, const Doors& doors) {
    for (auto strDirection : doors.DIRECTIONS){
        Direction d = doors.directions.at(getDirLetter(strDirection));
        os << strDirection << " " << d << " ";
    }
    return os;
}

/**
 * Override the << to print out a door in a specific direction
 * @param os
 * @param dir
 * @return
 */
std::ostream& operator<<(std::ostream& os, const Direction& dir) {
    if (dir.to > -1) {
        os << "ID:" << dir.to << " ";
    } else {
        os << "portal:" << dir.remoteLocation;
    }

    return os;
}

/**
 * Load the Door and direction information from a json object, from inside room
 * "doors": [
            {
                "dir": "north",
                "to": 54,
                "portal": null
            },
            {
                "dir": "south",
                "to": 5,
                "portal": null
            },...]
 * @param minAnum
 * @param jsonDoors
 */
void Doors::loadJson(int minAnum, const json& jsonDoors){
    for (auto strDirection : DIRECTIONS) {
        directions[getDirLetter(strDirection)] = Direction();
    }
    for (auto jd : jsonDoors.array_items()) { //know that has directions
        int to = -1;
        string remoteLocation = "";

        if (!jd["to"].is_null()) {
            int localAreaToVal = jd["to"].int_value();
            to = localAreaToVal + minAnum;
        }
        
        if (!jd["portal"].is_null()) {
            remoteLocation = jd["portal"].string_value();
        }
        
        //???
        Direction direction = directions.at(getDirLetter(jd["dir"].string_value()));
        direction.to = to;
        direction.remoteLocation = remoteLocation;
        directions[getDirLetter(jd["dir"].string_value())] = direction;
    }
}

/**
 * A direction has either an exit room ID or a remote location associatd with it
 * @return
 */
bool Direction::exists(){

    return false;
}

/**
 * Return a string list of the exits the current doors offer
 * @return
 */
string Doors::getExits(){

    ostringstream infoStream;



    return infoStream.str();
}

/**
 * Return the results of moving through a door in the given direction
 * @param direction
 * @param portals
 * @return
 */
int Doors::goThroughDoor(string direction, map<string, int> portals){
    cout << " Doors::goThroughDoo laceholder for compilation " << direction << " " << portals.at("a") << endl;
    return -1;

}

/**
 * Check if this set of doors has a remote location with the given portal name
 * @param key
 * @return
 */
int Doors::hasRemoteLocationNamed(const string& portalName){
    cout << "Doors::hasRemoteLocationNamed placeholder for compilation " << portalName << endl;
    return false;
}
