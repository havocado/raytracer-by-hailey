#include "mesh.h"
#include "vec3.h"
#include "ray.h"
#include "collisionData.h"

void Mesh::addVertex(const Point3& vertexPosition) {
    verticesLocalCoord.push_back(vertexPosition);
    verticesWorldCoord.push_back(this->localToWorld(vertexPosition));
}

void Mesh::addVertex(const float& v0, const float& v1, const float& v2) {
    verticesLocalCoord.emplace_back(v0, v1, v2);
    verticesWorldCoord.push_back(this->localToWorld(verticesLocalCoord[verticesLocalCoord.size()-1]));
}

void Mesh::addFace(const Face& face) {
    faces.push_back(face);
}

void Mesh::addFace(const int& vInd0, const int& vInd1, const int& vInd2) {
    faces.emplace_back(vInd0, vInd1, vInd2, this);
}

CollisionData Mesh::rayCollisionPoint(const Ray& r) {
    // Return collision with minimum t
    bool collided = false;
    float min_t = RAY_T_MAX;
    CollisionData closestCollision;
    for (auto & face : this->faces) {
        CollisionData coll = face.rayCollisionPoint(r);
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

void Mesh::rotateX(const float& theta) {
    this->rotationMatrix = rotationX(theta) * this->rotationMatrix;
    this->precomputeWorldCoords();
    this->precomputeFaceProperties();
}

void Mesh::rotateY(const float& theta) {
    this->rotationMatrix = rotationY(theta) * this->rotationMatrix;
    this->precomputeWorldCoords();
    this->precomputeFaceProperties();
}

void Mesh::rotateZ(const float& theta) {
    this->rotationMatrix = rotationZ(theta) * this->rotationMatrix;
    this->precomputeWorldCoords();
    this->precomputeFaceProperties();
}

void Mesh::precomputeWorldCoords() {
    for (int i = 0; i < this->verticesWorldCoord.size(); i++) {
        this->verticesWorldCoord[i] = this->rotationMatrix * this->verticesLocalCoord[i] + this->position;
    }
}

void Mesh::precomputeFaceProperties() {
    for (int i = 0; i < this->faces.size(); i++) {
        this->faces[i].precomputeLocalProperties();
        this->faces[i].precomputeWorldProperties();
    }
}

// Parameters Counterclockwise order
Face::Face(const int& vInd0, const int& vInd1, const int& vInd2, Mesh* mesh) {
    this->mesh = mesh;
    vertexIndices.push_back(vInd0);
    vertexIndices.push_back(vInd1);
    vertexIndices.push_back(vInd2);
    this->precomputeLocalProperties();
    this->precomputeWorldProperties();
}

CollisionData Face::rayCollisionPoint(const Ray& r) {
    Point3 A = this->mesh->verticesWorldCoord[this->vertexIndices[0]];
    Point3 B = this->mesh->verticesWorldCoord[this->vertexIndices[1]];
    Point3 C = this->mesh->verticesWorldCoord[this->vertexIndices[2]];
    // Get t for plane-ray intersection point
    float t = (-1.f) * (dot(this->worldNormal, r.origin()) + this->coeff) / (dot(this->worldNormal, r.direction()));
    if (t > 0.f) {
        // Test if intersection point is within the triangle
        // Check if all barycentric coordinates are positive
        // Note: triangle intersection check can be simpler, I am using barycentric coordinates for later.
        Point3 location = r.at(t);

        float denom = dot(cross(B-A, C-A), worldNormal);
        float alpha = dot(cross(C-B, location-B), worldNormal) / denom;
        float beta = dot(cross(A-C, location-C), worldNormal) / denom;
        float gamma = dot(cross(B-A, location-A), worldNormal) / denom;

        if (alpha >= 0.f && beta >= 0.f && gamma >= 0.f) {
            return {true, r, t, this->worldNormal};
        }
    }
    return {false};
}

void Face::precomputeLocalProperties() {
    // Read local coords
    Vec3 v0 = this->mesh->verticesLocalCoord[this->vertexIndices[0]];
    Vec3 v1 = this->mesh->verticesLocalCoord[this->vertexIndices[1]];
    Vec3 v2 = this->mesh->verticesLocalCoord[this->vertexIndices[2]];

    // Computing normal: cross product of two edges
    Vec3 e1 = v1 - v0;
    Vec3 e2 = v2 - v1;
    this->localNormal = unit_vector(cross(e1, e2));
}

void Face::precomputeWorldProperties() {
    // Read world coords
    Vec3 v0 = this->mesh->verticesWorldCoord[this->vertexIndices[0]];
    Vec3 v1 = this->mesh->verticesWorldCoord[this->vertexIndices[1]];
    Vec3 v2 = this->mesh->verticesWorldCoord[this->vertexIndices[2]];

    // Computing world normal: cross product of two world edges
    Vec3 e1 = v1 - v0;
    Vec3 e2 = v2 - v1;
    this->worldNormal = unit_vector(cross(e1, e2));

    // Computing coeff
    // See documentation (TODO: add link later)
    this->coeff = (-1.f) * dot(this->worldNormal, v0);
}