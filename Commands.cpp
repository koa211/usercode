//
// Created by etrickel on 10/21/2023.
//

#include "Commands.h"
#include <sstream>

/**
 * Convert a value from a string to input, if the conversion fails return -1
 * @param input
 * @return the new integer value
 */
int convertToNumeric(string input){
    int number =-1;
    cout << "placeholder to allow compilation " << input << " " <<  endl;
    return number;
}

/**
 * Get numeric input from the user
 * @return the integer value entered unless not convertible then a -1
 */
int getNumericInput(){
    string input;
    // GET FROM USER
    return convertToNumeric(input);
}

/**
 * Handle the commands entered by the player in the game loop
 * @param myWorld
 * @param player
 * @param input
 * @return
 */
bool Commands::doCommand(World *myWorld, Player *player, string input){

    if (input[0] == 'n' || input[0] == 's' || input[0] == 'e' || input[0] == 'w' || input[0] == 'u' || (input[0] == 'd' && (input.size()==1 || input[1] == 'o') ) ) {

        return true;
    }
    size_t space_pos = input.find(" ");
    string command = "";
    string commandParam = "";

    cout << "placeholder, remove this, added to make it possible to compile " << space_pos << " " << myWorld->getRoomInfo(0) << " " << player->getHitpoints() << endl;

    // Check if a space is found, if it is we may have a command param too

    if (command[0] == 't') {  // teleport

    }
    if (command[0] == 'l') {  // look
    }

    if (command[0] == 'g') {  // get

    }
    if (command[0] == 'h') {  // help
    }
    if (command[0] == 'i') {  // inventory
    }
    if (command[0] == 'd') {  // drop
    }
    if (command[0] == 'a') {  // attack
    }
    if (input == "exit" || input == "quit" || input == "q") {
        cout << "Exiting game loop. Goodbye!\n";
        return false;
    }
    return true;
}

/**
 * Get a list of commands
 * @return a list of possible commands the player might use
 */
string Commands::getCommands(){
    ostringstream infoStream;

    infoStream << "look, drop, get, inventory, teleport, help, and attack ";

    return infoStream.str();
}