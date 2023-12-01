#include "Mob.h"
#include <iostream>
#include "utils.h"

/**
 * Default mob constructor
 */
Mob::Mob(): name(""), description(""), level(-1),hit_dice(""), damage_dice(""){}

/**
 * Mob constructor from json, if json is_null, name is_null, description is_null, or level is_null then do nothing
 * if hit_dice or damage_dice are null then set to ""
 * Make sure to calculate the id from anum and minAnum
 * [
    {"mobile": {
        "area": "midgaard",
        "anum": 0,
        "name": "wizard",
        "short_descr": "the wizard",
        "long_descr": "A wizard walks around behind the counter, talking to himself.\n",
        "description": "The wizard looks old and senile, and yet he looks like a very powerful\nwizard. He is equipped with fine clothing, and is wearing many fine\nrings and bracelets.\n",
        "race": "human",
        ...
        "level": 23,
        "hitroll": 0,
        "hit_dice": "1d1+999",
        "mana_dice": "1d1+999",
        "damage_dice": "1d8+32",
        "dam_type": "magic",
        ...
    }}, ...]
 * @param anumMin
 * @param jsonMob
 */
Mob::Mob(int anumMin, json jsonMob){
    json arr = jsonMob.array_items();

    cout << "Doors::hasRemoteLocationNamed placeholder for compilation " << anumMin << " " << arr.dump() << endl;
}

/**
 * Getter for mob name
 * @return
 */
string  Mob::getName(){
    return name;
}

/**
 * Rolls for the Mob's hit points and returns the value
 * @return number of hit points the mob has at the start of combat
 */
int Mob::rollForHitPoints() {
    string strHD = hit_dice;
    if (hit_dice.size() == 0){
        strHD="1d8+10";
    }
    int hp = rollDiceWithModifier(strHD);
    return hp;
}

/**
 * If the mob does not have any damage_dice then default to "1d4+2", as attacks with their hands
 * @return the value of the attack
 */
int Mob::rollForAttack() {
    string strHD = damage_dice;
    if (strHD.size() == 0){
        strHD="1d4+2";
    }
    int attack = rollDiceWithModifier(strHD);
    return attack;
}

/**
 * Getter for mob's id
 * @return integer value
 */
int Mob::getMobId(){
    return id;
}