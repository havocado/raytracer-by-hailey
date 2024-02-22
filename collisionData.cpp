#include "collisionData.h"

Point3 CollisionData::location() const {
    if (!collided) {
        std::cout << "Warning: location information called for placeholder collisionData" << std::endl;
        return {};
    }
    return r.at(t);
}

Ray CollisionData::getNextRay() const {
    return collidedObject->material->getNextRay(*this);
}

Color CollisionData::getColor() const {
    return collidedObject->material->getColor();
}

bool CollisionData::isLight() const {
    return collidedObject->material->isLightSource;
}

Color CollisionData::getLight() const {
    return collidedObject->material->getLight();
}

