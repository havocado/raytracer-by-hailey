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
    return boundingBox.rayCollidesBox(r);
}

void HittableObject::setPosition(const Point3& pos) {
    this->position = pos;
}

void HittableObject::movePosition(const Point3& delta) {
    setPosition(position + delta);
}

void HittableObject::moveX(const float& deltaX) {
    this->movePosition({deltaX, 0.f, 0.f});
}

void HittableObject::moveY(const float& deltaY) {
    this->movePosition({0.f, deltaY, 0.f});
}

void HittableObject::moveZ(const float& deltaZ) {
    this->movePosition({0.f, 0.f, deltaZ});
}

void HittableObject::setRotation(const Matrix3x3& rot) {
    this->rotationMatrix = rot;
}

void HittableObject::rotate(const Matrix3x3& rot) {
    this->setRotation(rot * rotationMatrix);
}

void HittableObject::rotateX(const float& theta) {
    this->rotate(rotationX(theta));
}

void HittableObject::rotateY(const float& theta) {
    this->rotate(rotationY(theta));
}

void HittableObject::rotateZ(const float& theta) {
    this->rotate(rotationZ(theta));
}

Vec3 HittableObject::localToWorld(const Vec3& v) {
    return this->rotationMatrix * v + this->position;
}