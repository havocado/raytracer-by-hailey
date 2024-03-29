#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vec3.h"
#include "hittableObject.h"
#include "ray.h"
#include "collisionData.h"

class Face;

const int MAX_VERTEX_PER_MESH = 10000000;
const int MAX_FACE_PER_MESH = 10000000;

class Mesh: public HittableObject {
public:
    std::vector<Point3> verticesLocalCoord; // local coordinates wrt mesh position
    std::vector<Face> faces;

    std::vector<Point3> verticesWorldCoord; // Precomputed world coord

    Mesh(Material* material);

    Mesh(const Point3& pos, const Matrix3x3& rotMatrix, Material* material);

    void addVertex(const Point3& vertexPosition);

    void addVertex(const float& v0, const float& v1, const float& v2);

    void addFace(const Face& face);

    void addFace(const int& vInd0, const int& vInd1, const int& vInd2);

    CollisionData rayCollisionPoint(const Ray& r);

    void setPosition(const Point3& pos);
    void setRotation(const Matrix3x3& rot);

protected:
    // Precompute all Vertex World Coord
    void precomputeWorldCoords();
    // Precompute all face properties
    void precomputeFaceProperties();
};

class Face {
public:
    Mesh* mesh;
    std::vector<int> vertexIndices; // size: 3

    // Local coord precomputed properties
    Vec3 localNormal;

    // Counterclockwise order
    Face(const int& vInd0, const int& vInd1, const int& vInd2, Mesh* mesh);

    CollisionData rayCollisionPoint(const Ray& r);

    // World coord precomputed properties
    Vec3 worldNormal;
    float coeff; // plane equation: dot(normal, point)+coeff == 0

    // Precompute local normal and coeff
    void precomputeLocalProperties();
    // Precompute world normal and coeff
    void precomputeWorldProperties();
};

#endif //MESH_H
