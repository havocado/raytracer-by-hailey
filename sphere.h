#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>
#include "vec3.h"
#include "ray.h"
#include "hittableObject.h"

class sphere: hittableObject {
public:
    float radius;

    sphere(): hittableObject(), radius(1.f) {}

    sphere(const point3& pos, const float** rotMatrix, const float& radius)
        : hittableObject(pos, rotMatrix), radius(radius) {}

    void setRadius(const float& radius) {
        this->radius = radius;
    }

    collisionData rayCollisionPoint(const ray& r) {
        /* Ray-sphere intersection test.
         * Let ray: A+tB, sphere: center C, radius R. (all known except t)
         * Intersection condition: (A+tB-C)^2 = R^2
         * <=> t = B(A-C) + sqrt(B^2 * R^2)
         *  or t = B(A-C) - sqrt(B^2 * R^2)
         * We take the smallest positive t (unless DNE)
         * */
        float termInsideSqrt = dot(r.direction(), r.direction()) * this->radius * this->radius;
        if (termInsideSqrt > 0.f) {
            float firstTerm = dot(r.direction(), (r.origin() - this->position));
            float secondTerm = std::sqrt(termInsideSqrt);
            float smaller_t = firstTerm - secondTerm;
            float larger_t = firstTerm + secondTerm;
            if (smaller_t > 0.f) {
                point3 location = r.origin() + smaller_t * r.direction();
                return collisionData(true, location);
            }
            else if (larger_t > 0.f) {
                point3 location = r.origin() + larger_t * r.direction();
                return collisionData(true, location);
            }
            else {
                return collisionData(false);
            }
        }
        else if (termInsideSqrt == 0.f) {
            point3 t = r.direction() * (r.origin() - this->position);
            point3 location = r.origin() + t * r.direction();
            return collisionData(true, location);
        }
        else { // (termInsideSqrt < 0.f)
            return collisionData(false);
        }
    }

};


#endif //SPHERE_H
