#include "Mesh.h"
#include "vec3.h"
#include "ray.h"
#include "collisionData.h"


void Mesh::addVertex(const point3& vertexPosition) {
    vertices.push_back(vertexPosition);
}

void Mesh::addVertex(const float& v0, const float& v1, const float& v2) {
    vertices.emplace_back(v0, v1, v2);
}

void Mesh::addFace(const Face& face) {
    faces.push_back(face);
}

void Mesh::addFace(const int& vInd0, const int& vInd1, const int& vInd2) {
    faces.emplace_back(vInd0, vInd1, vInd2, this);
}

collisionData Mesh::rayCollisionPoint(const ray& r) {
    // Return collision with minimum t
    bool collided = false;
    float min_t = RAY_T_MAX;
    collisionData closestCollision;
    for (auto & face : this->faces) {
        collisionData coll = face.rayCollisionPoint(r);
        if (coll.collided && coll.t < min_t) {
            collided = true;
            min_t = coll.t;
            closestCollision = coll;
        }
    }
    if (collided) {
        return closestCollision;
    }
    else {
        return {false};
    }
}

// Parameters Counterclockwise order
Face::Face(const int& vInd0, const int& vInd1, const int& vInd2, Mesh* mesh) {
    this->mesh = mesh;
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

collisionData Face::rayCollisionPoint(const ray& r) {
    float t = (dot(this->normal, r.origin()) + this->coeff) / (dot(this->normal, r.direction()));
    if (t > 0.f) {
        return {true, r, t, this->normal};
    }
    else {
        return {false};
    }
}
