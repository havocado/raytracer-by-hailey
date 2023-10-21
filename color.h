/*
 * Credit: https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/colorutilityfunctions
 */

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using Color = vec3;

void writeColor(std::ostream &out, Color pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << std::endl;
}

#endif //COLOR_H