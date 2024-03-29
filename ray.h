/*
 * Credit: https://raytracing.github.io/books/RayTracingInOneWeekend.html#rays,asimplecamera,andbackground/therayclass
 */

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

const float T_THRESHOLD = 0.0005f;
const float RAY_T_MAX = 1e30;

class Ray {
public:
    Ray() {}

    Ray(const Point3& origin, const Vec3& direction, const int& kthBounce)
        : orig(origin), dir(direction/direction.length()), kthBounce(kthBounce) {}

    Point3 origin() const { return orig; }
    Vec3 direction() const { return dir; }

    Point3 at(float t) const {
        return orig + t*dir;
    }

    int kthBounce;

private:
    Point3 orig;
    Vec3 dir;
};

#endif //RAY_H
