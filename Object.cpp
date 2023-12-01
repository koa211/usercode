#include "Object.h"
#include <iostream>
#include <sstream>
using namespace std;
/**
 * Default constructor for Object
 */
Object::Object(){
    id = -1;
    name="";
    description="";
}

/**
 * Constructor that uses a json object to fill out the fields of the object
 * Make sure to check for is_null and set a default value in that case.
 * [
    {"object": {
        "area": "midgaard",
        "anum": 0,
        "new_format": true,
        "name": "barrel beer",
        "short_descr": "a barrel of beer",
        "description": "A beer barrel has been left here.",
        "material": "wood",
        "item_type": "drink",
        "extra_flags": null,
        "wear_flags": "take",
        "values": {
            "capacity": 300,
            "filled": 300,
            "liquid": "beer",
            "poisoned": false
        },
        "level": 0,
        "weight": 160,
        "cost": 75,
        "condition": 100,
        "extra_description": [],
        "affects": []
    }}, ... ]
 * @param minAnum
 * @param object
 */
Object::Object(int minAnum, json object){
    cout << "OBject:Object placeholder " << minAnum << " " << object.dump() << endl;
}

/**
 * Override the << so that *object can be used to print out the object's information.
 * @param os
 * @param object
 * @return
 */
std::ostream& operator<<(std::ostream& os, const Object& object) {
    os << "Object ID: " << object.id << endl;
    os << "Name: " << object.name << std::endl;
    os << "Description: " << object.description << std::endl;

    return os;
}

/**
 * Returns Object name
 * @return string of object information
 */
string Object::getObjectInfo() const {
    ostringstream infoStream;

    infoStream << name;

    return infoStream.str();
}

/**
 * Getter for object details (currently just description)
 * @return string containing details
 */
 string Object::getObjectDetails() const {
     return description;
 }

 /**
  * Getter for object id
  * @return
  */
 int Object::getObjectId(){
     return id;
 }

