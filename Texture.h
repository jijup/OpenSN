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

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stb_image/stb_image.h>

#ifndef _TEXTURE_H_
#define _TEXTURE_H_


class Texture {
public:
    Texture();
    ~Texture();

    // Reads in texture from file
    int readTexture();

    // Driver function accessed from outside class
    int generateTexture();

    GLuint texture;

private:
    // Texture dimensions
    int texWidth;
    int texHeight;
};

#endif
