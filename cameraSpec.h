#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "matrix3x3.h"

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

    void setPosition(const Point3& pos) {
        this->position = pos;
    }
    void movePosition(const Point3& offset) {
        this->position += offset;
    }

    void rotateX(const float& theta) {
        // stub
    }
    void rotateY(const float& theta) {
        // stub
    }
    void rotateZ(const float& theta) {
        // stub
    }
private:
    float aspect_ratio;
};

#endif //CAMERA_H
