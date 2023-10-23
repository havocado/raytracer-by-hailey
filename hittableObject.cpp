#include "hittableObject.h"

HittableObject::HittableObject(Material* material) {
    // initialize rotationMatrix with identity
    rotationMatrix = Matrix3x3();
    this->material = material;
}

HittableObject::HittableObject(const Point3& pos, const Matrix3x3& rotMatrix, Material* material) {
    this->position = pos;
    // Deep copy rotation matrix
    this->rotationMatrix = Matrix3x3(rotMatrix);
    this->material = material;
}

bool HittableObject::rayCollidesBoundingBox(const Ray& r) {
    // STUB - Bounding box should be implemented later
    return true;
}

Vec3 HittableObject::localToWorld(const Vec3& v) {
    return this->rotationMatrix * v + this->position;
}