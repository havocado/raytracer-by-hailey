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
    virtual std::vector<NdcPoint> createSamplePoints(const int& width, const int& height) {
        std::vector<NdcPoint> samplePoints;
        samplePoints.reserve(width * height);
        for (int j = height-1; j >= 0; j--) {
            for (int i = 0; i < width; i++) {
                float x = ((float)i + 0.5f) * 2.f / (float)width - 1.f;
                float y = ((float)j + 0.5f) * 2.f / (float)height - 1.f;
                samplePoints.emplace_back(x, y);
            }
        }

        return samplePoints;
    }
};

#endif //SAMPLER_H
