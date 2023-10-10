#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include "vec3.h"

class collisionData {
public:
    bool collided; // Important!! Below info are all garbage if this variable is false
    point3 location;
    // Constructor for when collided==false (omit collision location)
    collisionData(const bool& collided=false): collided(collided) {}
    // Constructor for when collided==true
    collisionData(const bool& collided, const point3& location)
        : collided(collided), location(location) {}
};

#endif //COLLISIONDATA_H
