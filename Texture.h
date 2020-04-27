/**
 * Texture.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of OpenGL-based texture generation.
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "Noise.h"
#include "Mesh.h"
#include "Shader.h"

#include <memory>
#include <OpenGP/types.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <stb_image/stb_image_write.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifndef _TEXTURE_H_
#define _TEXTURE_H_


class Texture {
public:
    Texture();
    ~Texture();

    // Reads in texture from file
    int readTexture();

    // Load square
    int setupSquareCoordinates();

    // Load cube
    int setupCubeCoordinates();

    // Load mesh
    int setupMeshCoordinates(std::vector<Mesh::s_Mesh> meshes);

    // Sets up buffers
    int setupBuffers(std::vector<Mesh::s_Mesh> meshes);

    // Saves framebuffer as PNG
    int savePNG(std::string filename, GLFWwindow* w);

    // Saves framebuffer as BMP
    int saveBMP(std::string filename, GLFWwindow* w);

    // Driver function accessed from outside class
    int generateTexture(std::vector<Noise::Point> noise, std::vector<Mesh::s_Mesh> meshes, std::string file);

    // OpenGL Variables
    GLuint VBO, VAO, EBO, texture;
    int texWidth, texHeight, numIndices;

    // Helper variables for translation
    float xRange, yRange, zRange, xMid, yMid, zMid;

    // Vertices and indices of mesh
    std::vector<GLfloat> pVertices;
    std::vector<GLuint> pIndices;
};

#endif
