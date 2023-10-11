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
        // See https://github.com/havocado/obj-raytracer/blob/main/implementation-details.md
        this->v.reserve(8);
        this->v.push_back(new Vertex(point3(-0.5f, -0.5f, 0.5f)));
        this->v.push_back(new Vertex(point3(0.5f, -0.5f, 0.5f)));
        this->v.push_back(new Vertex(point3(-0.5f, -0.5f, -0.5f)));
        this->v.push_back(new Vertex(point3(0.5f, -0.5f, -0.5f)));
        this->v.push_back(new Vertex(point3(-0.5f, 0.5f, 0.5f)));
        this->v.push_back(new Vertex(point3(0.5f, 0.5f, 0.5f)));
        this->v.push_back(new Vertex(point3(-0.5f, 0.5f, -0.5f)));
        this->v.push_back(new Vertex(point3(0.5f, 0.5f, -0.5f)));

        this->f.push_back(new Face())
    }
};

#endif //CUBE_H
