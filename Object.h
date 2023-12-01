#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "json11.hpp"

using json = json11::Json;
using namespace std;

class Object {
    int id;
    string name;
    string description;
public:

    Object();

    Object(int minAnum, json object);

    string getObjectInfo() const;
    string getObjectDetails() const;

    int getObjectId();

    friend std::ostream& operator<<(std::ostream& os, const Object& object);
};

#endif // OBJECT_H
