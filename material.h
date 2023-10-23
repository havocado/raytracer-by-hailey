#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "collisionData.h"

class CollisionData;

// Superclass is a default Material
class Material {
public:
    Color color;

    Material();
    Material(const Color& color);

    // Generate a ray probabilistically
    Ray getNextRay(const CollisionData& collisionData);

    Color getColor();
};



#endif //MATERIAL_H
