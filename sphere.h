#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>
#include "vec3.h"
#include "ray.h"
#include "hittableObject.h"

class Sphere: public HittableObject {
public:
    float radius;

    Sphere(Material* material): HittableObject(material), radius(1.f) {
        boundingBox.insertPoint(this->position + Point3(radius, radius, radius));
        boundingBox.insertPoint(this->position - Point3(radius, radius, radius));
    }

    Sphere(const Point3& pos, const Matrix3x3& rotMatrix, const float& radius, Material* material)
        : HittableObject(pos, rotMatrix, material), radius(radius) {
        boundingBox.insertPoint(this->position + Point3(radius, radius, radius));
        boundingBox.insertPoint(this->position - Point3(radius, radius, radius));
    }

    void setRadius(const float& radius) {
        this->radius = radius;
        boundingBox.resetToEmpty();
        boundingBox.insertPoint(this->position + Point3(radius, radius, radius));
        boundingBox.insertPoint(this->position - Point3(radius, radius, radius));
    }

    Vec3 getNormal(const Point3& pt) {
        return unit_vector(pt - this->position);
    }

    CollisionData rayCollisionPoint(const Ray& r) override {
        // Skip bounding box test, because sphere intersection is faster.

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
            if (smaller_t > T_THRESHOLD) {
                Point3 location = r.at(smaller_t);
                return {true, r, smaller_t, this->getNormal(location), this};
            }
            else if (larger_t > T_THRESHOLD) {
                Point3 location = r.at(larger_t);
                return {true, r, larger_t, this->getNormal(location), this};
            }
            else {
                return {false};
            }
        }
        else if (termInsideSqrt == T_THRESHOLD) {
            float t = (-1.f) * dot(r.direction(), r.origin() - this->position)/Bsq;
            Point3 location = r.at(t);
            return {true, r, t, this->getNormal(location), this};
        }
        else { // (termInsideSqrt < 0.f)
            return {false};
        }
    }
};

#endif //SPHERE_H
