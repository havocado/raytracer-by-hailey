#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "matrix3x3.h"

class cameraSpec {
public:
    // Extrinsic
    point3 position; // xyz [meters]
    matrix3x3 rotationMatrix;

    // Intrinsics
    float sensorWidth; // [meters]
    float sensorHeight; // [meters]

    float focal_length; // [meters]

    // Use APS-C Camera standard when params not specified
    cameraSpec(): sensorWidth(0.0236f), sensorHeight(0.0156f), focal_length(0.0233f) {
        this->aspect_ratio = (this->sensorWidth)/(this->sensorHeight);
    }

    void setPosition(const point3& pos) {
        this->position = pos;
    }
    void movePosition(const point3& offset) {
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
