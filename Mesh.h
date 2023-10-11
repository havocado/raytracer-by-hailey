#ifndef MESH_H
#define MESH_H

#include <vector>
#include "hittableObject.h"
#include "ray.h"

class Mesh;
class Face;

class Mesh: public hittableObject {
public:
    std::vector<point3> vertices; // local coordinates wrt mesh position
    std::vector<Face> faces;

    Mesh(): hittableObject() {}

    Mesh(const point3& pos, const matrix3x3& rotMatrix): hittableObject(pos, rotMatrix) {}

    void addVertex(const point3& vertexPosition) {
        vertices.push_back(vertexPosition);
    }

    void addFace(const Face& face) {
        faces.push_back(face);
    }

    void addFace(const int& vInd0, const int& vInd1, const int& vInd2) {
        faces.emplace_back(vInd0, vInd1, vInd2);
    }

    collisionData rayCollisionPoint(const ray& r) {

    }
};

class Face {
public:
    Mesh* mesh;

    std::vector<int> vertexIndices; // size: 3
    vec3 normal;
    float coeff; // plane equation: dot(normal, point)+coeff == 0

    // Counterclockwise order
    Face(const int& vInd0, const int& vInd1, const int& vInd2) {
        vertexIndices.push_back(vInd0);
        vertexIndices.push_back(vInd1);
        vertexIndices.push_back(vInd2);
        // Computing normal: cross product of two edges
        vec3 e1 = this->mesh->vertices[vInd1] - this->mesh->vertices[vInd0];
        vec3 e2 = this->mesh->vertices[vInd2] - this->mesh->vertices[vInd1];
        this->normal = unit_vector(cross(e1, e2));
        // Precomputing coefficient.
        // This is from plane equation: dot(normal,point)+coeff == 0
        // also known as D from plane equation Ax+By+Cz+D==0
        this->coeff = (-1.f) * dot(this->normal, this->mesh->vertices[vInd1]);
    }

    collisionData rayCollisionPoint(const ray& )
};

#endif //MESH_H
