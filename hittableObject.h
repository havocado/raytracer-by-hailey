#ifndef HITTABLEOBJECT_H
#define HITTABLEOBJECT_H

#include <cstring>
#include "vec3.h"
#include "collisionData.h"
#include "matrix3x3.h"

class HittableObject {
public:
    Point3 position;
    Matrix3x3 rotationMatrix;

    // Bounding box should be implemented later

    HittableObject() {
        // initialize rotationMatrix with identity
        rotationMatrix = Matrix3x3();
    }

    HittableObject(const Point3& pos, const Matrix3x3& rotMatrix) {
        this->position = pos;
        // Deep copy rotation matrix
        std::memcpy(&(this->rotationMatrix), &rotMatrix, sizeof(Matrix3x3));
    }

    bool rayCollidesBoundingBox(const Ray& r) {
        // STUB - Bounding box should be implemented later
        return true;
    }

    virtual CollisionData rayCollisionPoint(const Ray& r) = 0;
};

#endif //HITTABLEOBJECT_H
