#ifndef CUBE_H
#define CUBE_H

#include "vec3.h"
#include "Mesh.h"

class Cube: public Mesh {
public:
    float cubeDim[3]; // xyz

    Cube(): Mesh() { initMesh(1.f, 1.f, 1.f); }

    Cube(const point3& pos, const matrix3x3& rotMatrix): Mesh(pos, rotMatrix) {
        initMesh(1.f, 1.f, 1.f);
    }

    Cube(const float& dimX, const float& dimY, const float& dimZ): Mesh() {
        initMesh(dimX, dimY, dimZ);
    }

    Cube(const point3& pos, const matrix3x3& rotMatrix,
         const float& dimX, const float& dimY, const float& dimZ)
        : Mesh(pos, rotMatrix) {
        initMesh(dimX, dimY, dimZ);
    }

private:
    void initMesh(const float& dimX, const float& dimY, const float& dimZ) {
        this->cubeDim[0] = dimX;
        this->cubeDim[1] = dimY;
        this->cubeDim[2] = dimZ;
        this->addVertex(-(dimX/2.f), -(dimY/2.f), (dimZ/2.f));
        this->addVertex((dimX/2.f), -(dimY/2.f), (dimZ/2.f));
        this->addVertex(-(dimX/2.f), -(dimY/2.f), -(dimZ/2.f));
        this->addVertex((dimX/2.f), -(dimY/2.f), -(dimZ/2.f));
        this->addVertex(-(dimX/2.f), (dimY/2.f), (dimZ/2.f));
        this->addVertex((dimX/2.f), (dimY/2.f), (dimZ/2.f));
        this->addVertex(-(dimX/2.f), (dimY/2.f), -(dimZ/2.f));
        this->addVertex((dimX/2.f), (dimY/2.f), -(dimZ/2.f));

        this->addFace(0, 2, 1);
        this->addFace(1, 2, 3);
        this->addFace(1, 7, 5);
        this->addFace(1, 3, 7);
        this->addFace(6, 7, 3);
        this->addFace(6, 3, 2);
        this->addFace(4, 6, 2);
        this->addFace(4, 2, 0);
        this->addFace(4, 0, 5);
        this->addFace(5, 0, 1);
        this->addFace(6, 5, 7);
        this->addFace(6, 4, 5);
    }
};


#endif //CUBE_H
