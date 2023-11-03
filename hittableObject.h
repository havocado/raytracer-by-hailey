#ifndef HITTABLEOBJECT_H
#define HITTABLEOBJECT_H

#include <cstring>
#include "vec3.h"
#include "collisionData.h"
#include "matrix3x3.h"
#include "material.h"
#include "boundingBox.h"

class CollisionData;
class Material;

class HittableObject {
public:
    Point3 position;
    Matrix3x3 rotationMatrix;
    Material* material;
    BoundingBox boundingBox;

    // Bounding box should be implemented later

    HittableObject(Material* material);

    HittableObject(const Point3& pos, const Matrix3x3& rotMatrix, Material* material);

    bool rayCollidesBoundingBox(const Ray& r);

    virtual CollisionData rayCollisionPoint(const Ray& r) = 0;

    virtual void setPosition(const Point3& pos);

    void movePosition(const Point3& delta);

    void moveX(const float& deltaX);

    void moveY(const float& deltaY);

    void moveZ(const float& deltaZ);

    virtual void setRotation(const Matrix3x3& rot);

    void rotate(const Matrix3x3& rot);

    void rotateX(const float& theta);

    void rotateY(const float& theta);

    void rotateZ(const float& theta);

protected:
    Vec3 localToWorld(const Vec3& v);
};

#endif //HITTABLEOBJECT_H
