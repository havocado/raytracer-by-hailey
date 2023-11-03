#include "collisionData.h"

Point3 CollisionData::location() const {
    if (!collided) {
        std::cout << "Warning: location information called for placeholder collisionData" << std::endl;
        return {};
    }
    return r.at(t);
}

Ray CollisionData::getNextRay() {
    return collidedObject->material->getNextRay(*this);
}

Color CollisionData::getColor() {
    return collidedObject->material->getColor();
}

bool CollisionData::isLight() {
    return collidedObject->material->isLightSource;
}

Color CollisionData::getLight() {
    return collidedObject->material->getLight();
}

