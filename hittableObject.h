#ifndef HITTABLEOBJECT_H
#define HITTABLEOBJECT_H

#include <cstring>
#include "vec3.h"
#include "collisionData.h"
#include "matrix3x3.h"
#include "material.h"

class CollisionData;
class Material;

const float T_THRESHOLD = 0.0005f;

class HittableObject {
public:
    Point3 position;
    Matrix3x3 rotationMatrix;
    Material* material;

    // Bounding box should be implemented later

    HittableObject(Material* material);

    HittableObject(const Point3& pos, const Matrix3x3& rotMatrix, Material* material);

    bool rayCollidesBoundingBox(const Ray& r);

    virtual CollisionData rayCollisionPoint(const Ray& r) = 0;

protected:
    Vec3 localToWorld(const Vec3& v);
};

#endif //HITTABLEOBJECT_H
