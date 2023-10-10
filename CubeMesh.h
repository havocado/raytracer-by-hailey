#ifndef CUBE_H
#define CUBE_H

#include "Mesh.h"

class CubeMesh: public Mesh {
public:
    vec3 dim;

    CubeMesh() {
        initMesh(1.f, 1.f, 1.f);
    }

    CubeMesh(const vec3& dim) {
        initMesh(dim.x(), dim.y(), dim.z());
    }

    CubeMesh(const float& dimX, const float& dimY, const float& dimZ) {
        initMesh(dimX, dimY, dimZ);
    }

private:
    void initMesh(const float& dimX, const float& dimY, const float& dimZ) {
        this->v.reserve(8);
        this->v.emplace_back(point3(-0.5f, -0.));
    }
};

#endif //CUBE_H
