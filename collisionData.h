#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include <iostream>
#include "vec3.h"
#include "ray.h"

class CollisionData {
public:
    bool collided; // Important!! Below info are all garbage if this variable is false
    float t;
    Vec3 normal;
    Ray r;
    // Constructor for when collided==true
    CollisionData(const bool& collided, const Ray& r, const float& t, const Vec3& normal)
            : collided(collided), r(r), t(t), normal(normal) {}
    // Constructor for when collided==false (omit collision location)
    CollisionData(const bool& collided=false): collided(collided) {}

    Point3 location() const {
        if (!collided) {
            std::cout << "Warning: location information called for placeholder collisionData" << std::endl;
            return {};
        }
        return r.at(t);
    }
};

#endif //COLLISIONDATA_H
