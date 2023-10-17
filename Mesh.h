#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vec3.h"
#include "hittableObject.h"
#include "ray.h"
#include "collisionData.h"

class Face;

class Mesh: public hittableObject {
public:
    std::vector<point3> vertices; // local coordinates wrt mesh position
    std::vector<Face> faces;

    Mesh(): hittableObject() {}

    Mesh(const point3& pos, const matrix3x3& rotMatrix): hittableObject(pos, rotMatrix) {}

    void addVertex(const point3& vertexPosition);

    void addVertex(const float& v0, const float& v1, const float& v2);

    void addFace(const Face& face);

    void addFace(const int& vInd0, const int& vInd1, const int& vInd2);

    collisionData rayCollisionPoint(const ray& r);
};

class Face {
public:
    Mesh* mesh;

    std::vector<int> vertexIndices; // size: 3
    vec3 normal;
    float coeff; // plane equation: dot(normal, point)+coeff == 0

    // Counterclockwise order
    Face(const int& vInd0, const int& vInd1, const int& vInd2, Mesh* mesh);

    collisionData rayCollisionPoint(const ray& r);
};

#endif //MESH_H
