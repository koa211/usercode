//
// Created by etrickel on 10/21/2023.
//

#ifndef CPPMUD_UTILS_H
#define CPPMUD_UTILS_H
#include "utils.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "json11.hpp"
#include "World.h"

using namespace std;
using json = json11::Json;

/**
 * Rolls the dice that fit a damage dice string input
 * Example: 1d10+5, rolls for a value between 1 and 10 (inclusive, like a 10-sided dice) then adds 5 to the value
 * @param diceInput
 * @return the result of the dice roll
 */
int rollDiceWithModifier(const string& diceInput) {
    int numberOfDice, numberOfSides, modifier;

    // Find positions of 'd' and '+' in the input string
    size_t dPosition = diceInput.find('d');
    size_t plusPosition = diceInput.find('+');

    // Extract and convert substrings to integers
    numberOfDice = stoi(diceInput.substr(0, dPosition));
    if (plusPosition != string::npos) {
        numberOfSides = stoi(diceInput.substr(dPosition + 1, plusPosition - dPosition - 1));
        modifier = stoi(diceInput.substr(plusPosition + 1));
    } else {
        numberOfSides = stoi(diceInput.substr(dPosition + 1));
        modifier = 0;
    }


    int totalRoll = 0;
    for (int i = 0; i < numberOfDice; ++i) {
        totalRoll += rand() % numberOfSides + 1;
    }

    return totalRoll + modifier;
}


/**
 * Starting from the startPath search for the portals.json file, it should be located at data/config/portals.json
 * It makes this overkill, but also good prep for the next function.
 * Note: filesystem::recursive_directory_iterator(startPath) is only available in C++17 and newer.
 * @param startPath
 * @return
 */
string getConfigDirectory(const string& startPath) {
    vector<string> directories;

    for (const auto& entry : filesystem::recursive_directory_iterator(startPath)) {
        if (entry.is_regular_file() && entry.path().filename() == "portals.json") {
            return entry.path().parent_path().string();
        }
    }

    return "";
}

/**
 * Starting from the startPath perform a recursive directory seearch for every directory that contains the file
 * area.json. If we find area.json, get the entry.path().parent_path().string() and add it to the directories vector.
 * @param startPath
 * @return the directories vector
 */
vector<string> getDirectoriesWithAreaJson(const string& startPath) {
    vector<string> directories;
    
    for (const auto& entry : filesystem::recursive_directory_iterator(startPath)) {
        if (entry.is_regular_file() && entry.path().filename() == "area.json") {
            directories.push_back(entry.path().parent_path().string());
        }
    }

    return directories;
}

/**
 * This function reads the json file and returns json data
 * @param file_path
 * @return json data
 */
json read_json_file(const string &file_path) {
       std::ifstream t(file_path);
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());

    std::string err;
    const auto json = json11::Json::parse(str, err);
    return json;
}

/**
 * This gets the json data and loads it into each of the primary objects. It provides the minVnum from the current area
 *
 * @param datapath - where the data starts at
 * @param world    - an instantiation of the World class
 *
 */
void loadJsonData(const string &datapath, World *world){
    vector<string> dirs = getDirectoriesWithAreaJson(datapath);

    // this for loop is requiring a list of the directories that will contain the world information
    // example ['midgaard','moria','hell'...]
    for (const auto &entry : dirs){
        json area = read_json_file(entry + "/area.json");
        json rooms = read_json_file(entry + "/rooms.json");
        json objects = read_json_file(entry + "/objects.json");
        json mobs = read_json_file(entry + "/mobiles.json");

        int minVnum = area[0]["area"]["min_vnum"].int_value();

        if (!rooms.is_null()) {
            world->addRooms(minVnum, rooms);
        }
        //world->addObjects(minVnum, objects);
        //world->addMobs(minVnum, mobs);

    }
    string configDir = getConfigDirectory(datapath);
    json jsonPortals = read_json_file(configDir + "/portals.json");
    world->addPortals(jsonPortals);
}



/**
 * Given a string it returns a lower case version of it
 * @param str
 */
string stringToLower(std::string& str) {
    std::string lowercased;
    for (char c : str) {
        lowercased.push_back(std::tolower(static_cast<unsigned char>(c)));
    }
    return lowercased;
}

#endif //CPPMUD_UTILS_H
