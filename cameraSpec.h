#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

class cameraSpec {
public:
    // Extrinsic
    point3 position; // xyz [meters]
    float rotationMatrix[3][3]; // 3x3 matrix. This is temporary and should be replaced with quaternion in the future

    // Intrinsics
    float sensorWidth; // [meters]
    float sensorHeight; // [meters]

    float focal_length; // [meters]

    // Use APS-C Camera standard when params not specified
    cameraSpec(): sensorWidth(2.36f), sensorHeight(1.56f), focal_length(23.3f) {
        // initialize rotationMatrix with identity
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                rotationMatrix[i][j] = (i == j);
            }
        }
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
};

#endif //CAMERA_H
