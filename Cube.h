#ifndef CUBE_H
#define CUBE_H

#include "vec3.h"
#include "Mesh.h"

class Cube: public Mesh {
public:
    float cubeDim[3]; // xyz

    Cube(): Cube(1.f, 1.f, 1.f) {}

    Cube(const point3& pos, const matrix3x3& rotMatrix): Cube(pos, rotMatrix, 1.f, 1.f, 1.f) {}

    Cube(const float& dimX, const float& dimY, const float& dimZ) {
        cubeDim[0] = dimX;
        cubeDim[1] = dimY;
        cubeDim[2] = dimZ;
    }

    Cube(const point3& pos, const matrix3x3& rotMatrix,
         const float& dimX, const float& dimY, const float& dimZ)
        : Mesh(pos, rotMatrix) {
        cubeDim[0] = dimX;
        cubeDim[1] = dimY;
        cubeDim[2] = dimZ;
    }

};


#endif //CUBE_H
