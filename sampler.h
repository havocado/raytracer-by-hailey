#ifndef SAMPLER_H
#define SAMPLER_H

#include <vector>

struct NdcPoint {
    float x; // in [-1, 1]
    float y; // in [-1, 1]
    NdcPoint(const float& x, const float& y) : x(x), y(y) {}
};

class Sampler {
public:
    // Create points on screen that rays would be initiated from
    // Uniform sampling by default; Override in derived class
    virtual std::vector<NdcPoint> createSamplePoints(const int& width, const int& height);
};

#endif //SAMPLER_H
