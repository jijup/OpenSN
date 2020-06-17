/**
 * Texture.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of OpenGL-based texture generation.
 */

#include <icg_common.h>
#include "Texture.h"

Texture::Texture() {}

Texture::~Texture() {}

/*
 * Reads noise texture images from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::readNoiseTexture(GLuint *tex) {

    printf("\n    Attempting to read noise texture from file.\n");

    // Set our texture parameters and texture filtering
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Define filename of texture to read
    std::string filename = "../Output/temp/noise_output.bmp";

    // Read file
    int texWidth, texHeight;
    //stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(filename.c_str(), &texWidth, &texHeight, 0, 4);

    // Create texture and generate mipmaps
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Debug
    printf("        BMP file read: %s\n    Successfully read noise texture from file.\n", filename.c_str());

    // Cleanup
    stbi_image_free(image);

    return 0;
}

/*
 * Reads skybox texture images from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::readSkyboxTexture(unsigned int i, std::string filename) {

    printf("\n    Attempting to read skybox texture from file.\n");

    int texWidth, texHeight;

    unsigned char* image = stbi_load(filename.c_str(), &texWidth, &texHeight, 0, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Debug
    printf("        PNG file read: %s\n    Successfully read skybox texture from file.\n", filename.c_str());

    // Cleanup
    stbi_image_free(image);

    return 0;
}

/*
 * Reads terrain texture images from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::readTerrainTexture(int i, std::string filename) {
    printf("\n    Attempting to read terrain texture from file.\n");

    int texWidth, texHeight;

    unsigned char* image = stbi_load(filename.c_str(), &texWidth, &texHeight, 0, 4);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    //glGenerateMipmap(GL_TEXTURE_2D);

    int numMipmapLevels = 9;
    for (int i = 0; i < numMipmapLevels; i++) {
        glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    // Read texture from file
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, numMipmapLevels - 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);                       // MIPMAP doesn't apply to Magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Debug
    printf("        PNG file read: %s\n    Successfully read terrain texture from file.\n", filename.c_str());

    // Cleanup
    stbi_image_free(image);

    return 0;
}

/*
 * Generates noise texture from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::generateNoiseTexture(GLuint *tex) {

    // Read texture from file
    printf("\n    Starting noise texture generation.");
    Texture::readNoiseTexture(tex);
    printf("    Successfully completed noise texture generation.\n");

    return 0;
}

/*
 * Generates skybox texture from files.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::generateSkyboxTexture(int i, std::string filename) {

    // Read texture from file
    Texture::readSkyboxTexture(i, filename);

    return 0;
}

/*
 * Generates terrain textures from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::generateTerrainTexture(int i, std::string filename) {

    // Read texture from file
    Texture::readTerrainTexture(i, filename);

    return 0;
}


