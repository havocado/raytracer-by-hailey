#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>
#include "vec3.h"
#include "ray.h"
#include "hittableObject.h"

class sphere: public hittableObject {
public:
    float radius;

    sphere(): hittableObject(), radius(1.f) {}

    sphere(const point3& pos, const matrix3x3& rotMatrix, const float& radius)
        : hittableObject(pos, rotMatrix), radius(radius) {}

    void setRadius(const float& radius) {
        this->radius = radius;
    }

    vec3 getNormal(const point3& pt) {
        return (pt - this->position);
    }

    collisionData rayCollisionPoint(const ray& r) override {
        /* Ray-sphere intersection test.
         * Let ray: A+tB, sphere: center C, radius R. (all known except t)
         * Intersection condition: (A+tB-C)^2 = R^2
         * <=> t = (-B(A-C) + sqrt( (B(A-C))^2 - B^2 ((A-C)^2-R^2) )) / B^2
         *  or t = (-B(A-C) - sqrt( (B(A-C))^2 - B^2 ((A-C)^2-R^2) )) / B^2
         * We take the smallest positive t (unless DNE)
         * */
        float B_AC = dot(r.direction(), (r.origin() - this->position));
        float Bsq = dot(r.direction(), r.direction());
        float ACsq = dot(r.origin() - this->position, r.origin() - this->position);
        float termInsideSqrt = B_AC*B_AC - Bsq*(ACsq - (this->radius * this->radius));
        if (termInsideSqrt > 0.f) {
            float firstTerm = (-1.f) * dot(r.direction(), r.origin() - this->position);
            float secondTerm = std::sqrt(termInsideSqrt);
            float smaller_t = (firstTerm - secondTerm)/Bsq;
            float larger_t = (firstTerm + secondTerm)/Bsq;
            if (smaller_t > 0.f) {
                point3 location = r.at(smaller_t);
                return collisionData(true, location, this->getNormal(location));
            }
            else if (larger_t > 0.f) {
                point3 location = r.at(larger_t);
                return collisionData(true, location, this->getNormal(location));
            }
            else {
                return collisionData(false);
            }
        }
        else if (termInsideSqrt == 0.f) {
            float t = (-1.f) * dot(r.direction(), r.origin() - this->position)/Bsq;
            point3 location = r.at(t);
            return collisionData(true, location, this->getNormal(location));
        }
        else { // (termInsideSqrt < 0.f)
            return collisionData(false);
        }
    }
};

#endif //SPHERE_H
