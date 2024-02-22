#include "utils.h"

float calculateRaySurfaceCosAngle(const Ray& r, const Vec3& n) {
    float dotProd = dot(r.direction(), n*(-1.f));
    float dotProdNormalized = dotProd / (r.direction().length() * n.length());
    return dotProdNormalized;
}