#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "vec3.h"
#include "ray.h"

class BoundingBox {
public:
    bool isEmpty;
    Point3 AabbMin;
    Point3 AabbMax;

    BoundingBox(): isEmpty(true) {}

    bool rayCollidesBox(const Ray& ray);

    void insertPoint(const Point3& pt);

    void resetToEmpty();
};


#endif //BOUNDINGBOX_H
