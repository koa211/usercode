//
// Created by etrickel on 10/20/2023.
//
#include "Object.h"
#include "Player.h"
#include "utils.h"

using namespace std;

/**
 * Default constructor for Player
 */
Player::Player(){

}

/**
 * getter for location (i.e., room Id)
 * @return the player's current room Id
 */
int Player::getLocation(){
    return location;
}

/**
 * set the players new location, when moving or what not
 * @param newLocation
 */
void Player::setLocation(int newLocation){
    location = newLocation;
}

/**
 * Add an object Id to the player's invetory
 * @param objId
 */
void Player::addToInventory(int objId) {
    inventory.push_back(objId);
}

/**
 * Get a vector that contains the object Ids that the player posses.
 * @return
 */
vector<int> Player::getInventory() {
    return inventory;
}

/**
 * Given an index as input remove the inventory item at that index
 * @param indexToRemove
 * @return
 */
int Player::removeObjectFromInventory(int indexToRemove){

    cout << "Player::removeObjectFromInventory placeholder " << indexToRemove << endl;

    return -1;
}

/**
 * return true if the player has 1 or more items in their inventory
 * @return
 */
bool Player::hasItems(){
    return inventory.size() > 0;
}

/**
 * Getter for the player's hitpoints
 * @return
 */
int Player::getHitpoints() {
    return hitpoints;
}

/**
 * Perfoms an attack using the player's dice. If the player doesn't have any dice it defaults to
 * a supremely powerful weapon because why not?  Feel free to change
 * @return the value of the attack
 */
int Player::rollForAttack() {
    string strHD = "";
    if (strHD.size() == 0){
        strHD="1d100+500";
    }
    int attack = rollDiceWithModifier(strHD);
    return attack;
}

/**
 * Changes the player's location, basically a setLocation, but can have more logic wrapped around the set.
 * @param loc
 */
void Player::teleport(int loc){
    location = loc;
}