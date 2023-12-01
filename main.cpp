#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "World.h"
#include "Game.h"
#include "utils.h"

using namespace std;

/**
 * main function that starts off the mud
 * @return 0
 */
int main() {
    // Seed for random number generation
    srand(time(nullptr));

    string config_data = "./data";
    auto *myWorld = new World();

    loadJsonData(config_data, myWorld);

    Game game(myWorld);
    game.start();

    return 0;
}
