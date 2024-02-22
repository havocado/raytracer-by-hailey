#ifndef UTILS_H
#define UTILS_H

#include "vec3.h"
#include "ray.h"
#include "cameraSpec.h"

std::pair<int, int> getWindowDim(const CameraSpec& camera, const int& numPixelWidth);

float calculateRaySurfaceCosAngle(const Ray& r, const Vec3& n);

#endif //UTILS_H
