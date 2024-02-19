#include "sampler.h"

// Create points on screen that rays would be initiated from
// Uniform sampling by default; Override in derived class
std::vector<NdcPoint> Sampler::createSamplePoints(const int& width, const int& height) {
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