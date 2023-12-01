#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <iostream>
#include <string>
#include "json11.hpp"
#include <map>

using json = json11::Json;
using namespace std;

class Direction {
    bool exists();
    int to;
    std::string remoteLocation;

public:

    explicit Direction(int to=-1, string remoteLocation="");

    friend std::ostream& operator<<(std::ostream& os, const Direction& dir);

    friend class Doors;
};

class Doors {
private:
    map<string, Direction> directions;

public:
    int MAX_DIRS = 6;
    enum DIRS {NORTH, SOUTH, EAST, WEST, UP, DOWN};
    string DIRECTIONS[6] = {"North","South","East","West","Up","Down"};

    Doors();

    void loadJson(int minAnum, const json& jsonDir);

    string getExits();
    int goThroughDoor(string direction, map<string, int> portals);
    int hasRemoteLocationNamed(const string& key);
    friend std::ostream& operator<<(std::ostream& os, const Doors& doors);
};

#endif
