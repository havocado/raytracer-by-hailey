#ifndef MESH_H
#define MESH_H

#include <vector>
#include "hittableObject.h"
#include "vec3.h"

class Mesh;
class Halfedge;
class Vertex;
class Edge;
class Face;

class Mesh: public hittableObject {
public:
    int numVertices;
    int numEdges;
    int numFaces;

    Mesh(): numVertices(0), numEdges(0), numFaces(0) {}

    Vertex* getRoot() {
        return v[0];
    }

    ~Mesh() {
        // TODO: destruct all vertices
    }
protected:
    // List of pointers to Vertex/Edge/Face objects
    // All Vertex/Edge/Face are assumed to be connected
    std::vector<Vertex*> v;
    std::vector<Edge*> e;
    std::vector<Face*> f;
};

class Halfedge {
    Halfedge* twin;
    Halfedge* next;
    Vertex* vertex;
    Edge* edge;
    Face* face;
};

class Vertex {
public:
    point3 position;
    point3 normal;
    Halfedge* halfedge;

    Vertex(const point3& position, const point3& normal)
            : position(position), normal(normal) {}

    // When normal not specified, normal is same as position
    Vertex(const point3& position)
            : position(position), normal(unit_vector(position)) {}
};

class Edge {
public:
    Halfedge* halfedge;

    Edge() {}
};

class Face {
public:
    Halfedge* halfedge;
    vec3 normal;

    Face
};


#endif //MESH_H
