//
// Created by etrickel on 10/21/2023.
//

#ifndef CPPMUD_UTILS_H
#define CPPMUD_UTILS_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "json11.hpp"
#include "World.h"

using namespace std;
using json = json11::Json;

int rollDiceWithModifier(const string& diceInput);

void loadJsonData(const string &datapath, World *world);

string stringToLower(std::string& str);

#endif //CPPMUD_UTILS_H
