#include "boundingBox.h"

bool BoundingBox::rayCollidesBox(const Ray& ray) {
    // 1. (To avoid division by zero and some other obvious cases)
    // Compute two points: ray.at(T_THRESHOLD) and ray.at(RAY_T_MAX)
    // Make sure each x, y, z coordinates cross at least one of the 2 sides of box.
    Point3 rayAtZero = ray.at(T_THRESHOLD);
    Point3 rayAtInf = ray.at(RAY_T_MAX);
    if ( (rayAtZero.x() < AabbMin.x() && rayAtInf.x() < AabbMin.x())
        || (rayAtZero.x() > AabbMax.x() && rayAtInf.x() > AabbMax.x())
        || (rayAtZero.y() < AabbMin.y() && rayAtInf.y() < AabbMin.y())
        || (rayAtZero.y() > AabbMax.y() && rayAtInf.y() > AabbMax.y())
        || (rayAtZero.z() < AabbMin.z() && rayAtInf.z() < AabbMin.z())
        || (rayAtZero.z() > AabbMax.z() && rayAtInf.z() > AabbMax.z()) ) {
        return false;
    }
    // Test for intersection locations in each axes
    float tAtLowerX = (AabbMin.x() - ray.origin().x())/ray.direction().x();
    Point3 coordAtLowerX = ray.at(tAtLowerX);
    if (AabbMin.y() <= coordAtLowerX.y() && coordAtLowerX.y() <= AabbMax.y()
        && AabbMin.z() <= coordAtLowerX.z() && coordAtLowerX.z() <= AabbMax.z()) {
        return true;
    }
    float tAtUpperX = (AabbMax.x() - ray.origin().x())/ray.direction().x();
    Point3 coordAtUpperX = ray.at(tAtUpperX);
    if (AabbMin.y() <= coordAtUpperX.y() && coordAtUpperX.y() <= AabbMax.y()
        && AabbMin.z() <= coordAtUpperX.z() && coordAtUpperX.z() <= AabbMax.z()) {
        return true;
    }

    float tAtLowerY = (AabbMin.y() - ray.origin().y())/ray.direction().y();
    Point3 coordAtLowerY = ray.at(tAtLowerY);
    if (AabbMin.x() <= coordAtLowerY.x() && coordAtLowerY.x() <= AabbMax.x()
        && AabbMin.z() <= coordAtLowerY.z() && coordAtLowerY.z() <= AabbMax.z()) {
        return true;
    }
    float tAtUpperY = (AabbMax.y() - ray.origin().y())/ray.direction().y();
    Point3 coordAtUpperY = ray.at(tAtUpperY);
    if (AabbMin.x() <= coordAtUpperY.x() && coordAtUpperY.x() <= AabbMax.x()
        && AabbMin.z() <= coordAtUpperY.z() && coordAtUpperY.z() <= AabbMax.z()) {
        return true;
    }

    float tAtLowerZ = (AabbMin.z() - ray.origin().z())/ray.direction().z();
    Point3 coordAtLowerZ = ray.at(tAtLowerZ);
    if (AabbMin.x() <= coordAtLowerZ.x() && coordAtLowerZ.x() <= AabbMax.x()
        && AabbMin.y() <= coordAtLowerZ.y() && coordAtLowerZ.y() <= AabbMax.y()) {
        return true;
    }
    float tAtUpperZ = (AabbMax.z() - ray.origin().z())/ray.direction().z();
    Point3 coordAtUpperZ = ray.at(tAtUpperZ);
    if (AabbMin.x() <= coordAtUpperZ.x() && coordAtUpperZ.x() <= AabbMax.x()
        && AabbMin.y() <= coordAtUpperZ.y() && coordAtUpperZ.y() <= AabbMax.y()) {
        return true;
    }

    return false;
}

void BoundingBox::insertPoint(const Point3& pt) {
    if (isEmpty) {
        AabbMin = pt;
        AabbMax = pt;
        isEmpty = false;
    }
    else {
        AabbMin = Point3(std::min(pt.x(), AabbMin.x()),
                         std::min(pt.y(), AabbMin.y()),
                         std::min(pt.z(), AabbMin.z()));
        AabbMax = Point3(std::max(pt.x(), AabbMax.x()),
                         std::max(pt.y(), AabbMax.y()),
                         std::max(pt.z(), AabbMax.z()));
    }
}

void BoundingBox::resetToEmpty() {
    this->isEmpty = true;
}

