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

    // Creates a mesh from an OBJ file
    void generateFileMesh();

    // Creates a flat mesh
    void generateFlatMesh(int width, int height, std::vector<Noise::Point> noise);

    // Creates cube mesh
    void generateCubeMesh();

    //
    void generateSphereMesh();

    // Driver function accessed from outside class for mesh generation via external file
    void generateMeshFromFile();

    // Driver function accessed from outside class for mesh generation via Noise
    void generateMeshFromNoise(int width, int height, std::vector<Noise::Point> noise);

    // Driver function accessed from outside class for mesh generation for skybox
    void generateSkybox();

    void generatePlanet();

    // Mesh variables
    int numIndices;
    GLfloat *verticesMesh;
    GLuint *indicesMesh;

    int numIndicesPlanet;
    GLfloat *verticesMeshPlanet;
    GLuint *indicesMeshPlanet;

    int numIndicesSkybox;
    GLfloat *verticesMeshSkybox;
    GLuint *indicesMeshSkybox;
};

#endif
