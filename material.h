#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "collisionData.h"

class CollisionData;

// Superclass is a default Material
class Material {
public:
    bool isLightSource = false;
    Color color;

    Material();
    Material(const Color& color, const bool& isLightSource=false);

    // Generate a ray probabilistically
    Ray getNextRay(const CollisionData& collisionData);

    Color getColor();
    Color getLight();
};



#endif //MATERIAL_H
