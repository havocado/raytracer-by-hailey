#ifndef PLYIMPORT_H
#define PLYIMPORT_H

#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include "hittableObject.h"
#include "mesh.h"
#include "material.h"

/* This code is written to import stanford bunny, and it is not a general ply importer.
 * Since I doubt anyone else than myself would actually want to run this code, I'm not going to write a full ply importer
 * that handles every corner cases so please leave an issue if you really need support for other ply files
 * */

class plyImport {
public:
    static Mesh read(const std::string& fileName, Material& material) {
        std::ifstream targetFile(fileName);

        assert(targetFile.is_open() && "File open success");

        std::string plyStr;
        targetFile >> plyStr;
        assert(plyStr == "ply" && "File format is PLY");

        std::string formatStr;
        targetFile >> formatStr;
        while (formatStr == "comment") {
            getline(targetFile, formatStr);
            targetFile >> formatStr;
        }

        assert(formatStr == "format" && "format ascii 1.0");
        targetFile >> formatStr;
        assert(formatStr == "ascii" && "format ascii 1.0");
        targetFile >> formatStr;
        assert(formatStr == "1.0" && "format ascii 1.0");

        targetFile >> formatStr;
        Mesh mesh(&material);
        int vertexCount, faceCount;

        // 'element vertex 453'
        while (formatStr == "comment") {
            getline(targetFile, formatStr);
            targetFile >> formatStr;
        }
        assert(formatStr == "element");
        std::string elemTypeStr;
        targetFile >> elemTypeStr;
        assert(elemTypeStr == "vertex");
        targetFile >> vertexCount;
        assert(vertexCount > 0);
        assert(vertexCount <= MAX_VERTEX_PER_MESH);

        // 'property float x'
        int xyz[3];
        int vertexPropertyCount = 0;
        targetFile >> formatStr;
        while (formatStr == "property") {
            targetFile >> elemTypeStr;
            targetFile >> elemTypeStr;
            if (elemTypeStr == "x") {
                xyz[0] = vertexPropertyCount;
            }
            else if (elemTypeStr == "y") {
                xyz[1] = vertexPropertyCount;
            }
            else if (elemTypeStr == "z") {
                xyz[2] = vertexPropertyCount;
            }
            vertexPropertyCount++;
            targetFile >> formatStr;
        }

        // 'element face 948'
        assert(formatStr == "element");
        targetFile >> elemTypeStr;
        assert(elemTypeStr == "face");
        targetFile >> faceCount;
        assert(faceCount > 0);
        assert(faceCount <= MAX_FACE_PER_MESH);

        // 'property list uchar int vertex_indices'
        targetFile >> formatStr;
        assert(formatStr == "property");
        targetFile >> formatStr;
        assert(formatStr == "list");
        targetFile >> formatStr;
        assert(formatStr == "uchar" && "Face format not in form of 'property list uchar int vertex_indices'! Please rewrite the plyImport code to handle this format");
        targetFile >> formatStr;
        assert(formatStr == "int" && "Face format not in form of 'property list uchar int vertex_indices'! Please rewrite the plyImport code to handle this format");
        targetFile >> formatStr;
        assert((formatStr == "vertex_indices" || formatStr == "vertex_index") && "Face format not in form of 'property list uchar int vertex_indices'! Please rewrite the plyImport code to handle this format");

        targetFile >> formatStr;
        assert(formatStr == "end_header");

        // Read vertices
        float a[vertexPropertyCount];
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexPropertyCount; j++) {
                targetFile >> a[j];
            }
            mesh.addVertex(a[xyz[0]], a[xyz[1]], a[xyz[2]]);
        }

        // Read faces
        for (int i = 0; i < faceCount; i++) {
            int kVertexInFace;
            int v0, v1, v2;
            targetFile >> kVertexInFace;
            targetFile >> v0 >> v1 >> v2;
            mesh.addFace(v0, v1, v2);
            // handle cases where there are more than 3 vertices on a face
            for (int j = 3; j < kVertexInFace; j++) {
                v1 = v2;
                targetFile >> v2;
                mesh.addFace(v0, v1, v2);
            }
        }

        targetFile.close();

        return mesh;
    }
};

#endif //PLYIMPORT_H
