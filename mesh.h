#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vec3.h"
#include "hittableObject.h"
#include "ray.h"
#include "collisionData.h"

class Face;

class Mesh: public HittableObject {
public:
    std::vector<Point3> vertices; // local coordinates wrt mesh position
    std::vector<Face> faces;

    Mesh(): HittableObject() {}

    Mesh(const Point3& pos, const Matrix3x3& rotMatrix): HittableObject(pos, rotMatrix) {}

    void addVertex(const Point3& vertexPosition);

    void addVertex(const float& v0, const float& v1, const float& v2);

    void addFace(const Face& face);

    void addFace(const int& vInd0, const int& vInd1, const int& vInd2);

    CollisionData rayCollisionPoint(const Ray& r);
};

class Face {
public:
    Mesh* mesh;

    std::vector<int> vertexIndices; // size: 3
    Vec3 normal;
    float coeff; // plane equation: dot(normal, point)+coeff == 0

    // Counterclockwise order
    Face(const int& vInd0, const int& vInd1, const int& vInd2, Mesh* mesh);

    CollisionData rayCollisionPoint(const Ray& r);
};

#endif //MESH_H
