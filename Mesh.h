/**
 * Mesh.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of mesh generation.
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include <memory>
#include <OpenGP/types.h>
#include <glm/glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifndef _MESH_H_
#define _MESH_H_

class Mesh {
public:
    Mesh();
    ~Mesh();

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    struct s_Mesh {

        // Declare per mesh variables
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        s_Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
            this->vertices = vertices;
            this->indices  = indices;
        }
    };

    // Creates a mesh from an OBJ file
    void readObjIntoMesh();

    // Driver function accessed from outside class
    std::vector<Mesh::s_Mesh> generateMesh();

    // Declare mesh vector
    std::vector<Mesh::s_Mesh> meshes;
};

#endif
