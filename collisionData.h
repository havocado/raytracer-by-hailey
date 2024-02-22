#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include <iostream>
#include "hittableObject.h"
#include "vec3.h"
#include "ray.h"

class HittableObject;

class CollisionData {
public:
    bool collided; // Important!! Below info are all garbage if this variable is false
    float t;
    Vec3 normal;
    Ray r;
    HittableObject *collidedObject;

    // Constructor for when collided==true
    CollisionData(const bool &collided, const Ray &r, const float &t, const Vec3 &normal,
                  HittableObject *collidedObject)
            : collided(collided), r(r), t(t), normal(normal), collidedObject(collidedObject) {}

    // Constructor for when collided==false (omit collision location)
    CollisionData(const bool &collided = false) : collided(collided) {}

    Point3 location() const;
    Ray getNextRay() const;
    Color getColor() const;
    bool isLight() const;
    Color getLight() const;
};

#endif //COLLISIONDATA_H
