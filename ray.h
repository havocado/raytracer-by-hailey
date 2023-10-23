/*
 * Credit: https://raytracing.github.io/books/RayTracingInOneWeekend.html#rays,asimplecamera,andbackground/therayclass
 */

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

const float RAY_T_MAX = 1e30;

class Ray {
public:
    Ray() {}

    Ray(const Point3& origin, const Vec3& direction) : orig(origin), dir(direction/direction.length()) {}

    Point3 origin() const { return orig; }
    Vec3 direction() const { return dir; }

    Point3 at(float t) const {
        return orig + t*dir;
    }

private:
    Point3 orig;
    Vec3 dir;
};

#endif //RAY_H
