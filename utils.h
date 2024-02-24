#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "cameraSpec.h"

void readFile2Str(std::string& content, const std::string& filename);

unsigned int compileShader(unsigned int type, const std::string& source);

unsigned int createShader(const std::string& vertShader, const std::string& fragShader);

std::pair<int, int> getResolution(const CameraSpec& camera, const int& numPixelWidth);

float calculateRaySurfaceCosAngle(const Ray& r, const Vec3& n);

#endif //UTILS_H
