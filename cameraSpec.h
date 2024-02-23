#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"
#include "matrix3x3.h"
#include "sampler.h"

class CameraSpec {
public:
    // Extrinsic
    Point3 position; // xyz [meters]
    Matrix3x3 rotationMatrix;

    // Intrinsics
    float sensorWidth; // [meters]
    float sensorHeight; // [meters]
    float focal_length; // [meters]

    // Use APS-C Camera standard when params not specified
    CameraSpec(): sensorWidth(0.0236f), sensorHeight(0.0156f), focal_length(0.0233f) {
        this->aspect_ratio = (this->sensorWidth)/(this->sensorHeight);
    }

    Ray getRay(const NdcPoint& ndcPoint, const int& screenWidth, const int& screenHeight) const {
        Point3 A = Point3(ndcPoint.x, ndcPoint.y, -1.f * this->focal_length);
        Point3 B = A * Point3(this->sensorWidth, this->sensorHeight, this->focal_length);
        Point3 rayScreenDirection = rotationMatrix * B;
        return {this->position, rayScreenDirection, 0};
    }

    void setPosition(const Point3& pos) {
        this->position = pos;
    }

    void moveX(const float& deltaX) {
        this->movePosition({deltaX, 0.f, 0.f});
    }

    void moveY(const float& deltaY) {
        this->movePosition({0.f, deltaY, 0.f});
    }

    void moveZ(const float& deltaZ) {
        this->movePosition({0.f, 0.f, deltaZ});
    }

    void movePosition(const Point3& offset) {
        this->position += offset;
    }

    void rotateX(const float& theta) {
        this->rotationMatrix = rotationX(theta) * this->rotationMatrix;
    }
    void rotateY(const float& theta) {
        this->rotationMatrix = rotationY(theta) * this->rotationMatrix;
    }
    void rotateZ(const float& theta) {
        this->rotationMatrix = rotationZ(theta) * this->rotationMatrix;
    }
private:
    float aspect_ratio;
};

#endif //CAMERA_H
