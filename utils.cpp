#include "utils.h"

std::pair<int, int> getWindowDim(const CameraSpec& camera, const int& numPixelWidth) {
    return {numPixelWidth, std::round((float)numPixelWidth * camera.sensorHeight / camera.sensorWidth)};
}

float calculateRaySurfaceCosAngle(const Ray& r, const Vec3& n) {
    float dotProd = dot(r.direction(), n*(-1.f));
    float dotProdNormalized = dotProd / (r.direction().length() * n.length());
    return dotProdNormalized;
}