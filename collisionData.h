#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include "vec3.h"

class collisionData {
public:
    bool collided; // Important!! Below info are all garbage if this variable is false
    float t;
    vec3 normal;
    // Constructor for when collided==false (omit collision location)
    collisionData(const bool& collided=false): collided(collided) {}
    // Constructor for when collided==true
    collisionData(const bool& collided, const ray& r, const float& t, const vec3& normal)
        : collided(collided), t(t), normal(normal) {}
};

#endif //COLLISIONDATA_H
