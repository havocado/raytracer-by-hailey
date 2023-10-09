#ifndef HITTABLEOBJECT_H
#define HITTABLEOBJECT_H

#include <cstring>
#include "vec3.h"
#include "collisionData.h"
#include "matrix3x3.h"

class hittableObject {
public:
    point3 position;
    matrix3x3 rotationMatrix;

    // Bounding box should be implemented later

    hittableObject() {
        // initialize rotationMatrix with identity
        rotationMatrix = matrix3x3();
    }

    hittableObject(const point3& pos, const matrix3x3& rotMatrix) {
        this->position = pos;
        // Deep copy rotation matrix
        std::memcpy(&(this->rotationMatrix), &rotMatrix, sizeof(matrix3x3));
    }

    bool rayCollidesBoundingBox(const ray& r) {
        // STUB - Bounding box should be implemented later
        return true;
    }

    virtual collisionData rayCollisionPoint(const ray& r) = 0;
};

#endif //HITTABLEOBJECT_H
