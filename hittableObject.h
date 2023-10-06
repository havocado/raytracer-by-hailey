#ifndef HITTABLEOBJECT_H
#define HITTABLEOBJECT_H

#include "vec3.h"
#include "collisionData.h"

class hittableObject {
public:
    point3 position;
    float rotationMatrix[3][3];

    // Bounding box should be implemented later

    hittableObject() {
        // initialize rotationMatrix with identity
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                rotationMatrix[i][j] = (i == j);
            }
        }
    }

    hittableObject(const point3& pos, const float** rotMatrix) {
        this->position = pos;
        // Deep copy rotation matrix
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                rotationMatrix[i][j] = rotMatrix[i][j];
            }
        }
    }

    bool rayCollidesBoundingBox(const ray& r) {
        // STUB - Bounding box should be implemented later
        return true;
    }

    virtual collisionData rayCollisionPoint(const ray& r) = 0;
};

#endif //HITTABLEOBJECT_H
