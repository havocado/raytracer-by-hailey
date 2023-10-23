#include <stdlib.h>
#include "material.h"

Material::Material() {
    color = Color(0.5f, 0.5f, 0.5f);
}

Material::Material(const Color& color): color(color) {}

Ray Material::getNextRay(const CollisionData& collisionData) {
    //return {collisionData.location(), collisionData.r.direction() * (-1.f)};
    float dirX = (float)(std::rand())/RAND_MAX - 0.5f;
    float dirY = (float)(std::rand())/RAND_MAX - 0.5f;
    float dirZ = (float)(std::rand())/RAND_MAX - 0.5f;
    Vec3 direction(dirX, dirY, dirZ);
    float temp = dot(direction, collisionData.normal);
    if (dot(direction, collisionData.normal) < 0.f) {
        direction = direction * (-1.f);
    }
    return {collisionData.location(), direction};
}

Color Material::getColor() {
    return color;
}