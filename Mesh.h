/**
 * Mesh.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of meshes generated from OBJ files.
 */

#include "Noise.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include <memory>
#include <OpenGP/types.h>
#include <glm/glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

    // Creates a mesh from Perlin noise values
    void readNoiseIntoMesh(std::vector<Noise::Point> noise, int width, int height);

    // Driver function accessed from outside class for mesh generation via external file
    void generateMeshFromFile();

    // Driver function accessed from outside class for mesh generation via Noise
    void generateMeshFromNoise(std::vector<Noise::Point> noise, int width, int height);

    // Setup mesh coordinates for rendering
    int setupMeshCoordinates();

    // Declare mesh vector
    std::vector<Mesh::s_Mesh> meshes;

    // Vertices and indices of mesh
    std::vector<GLfloat> pVertices;
    std::vector<GLuint> pIndices;
    int numIndices;
};

#endif
