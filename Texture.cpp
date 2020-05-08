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
 * Reads texture image from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::readTexture() {

    printf("\nAttempting to read texture from file.\n");

    glGenTextures( 1, &this->texture );
    glBindTexture( GL_TEXTURE_2D, texture );

    // Set our texture parameters and texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Define filename of texture to read
    std::string filename = "../Output/temp/noise_output.bmp";

    // TODO: ADD FORMAT FROM NOISE VECTOR
    // Create texture and generate mipmaps
    unsigned char* image = stbi_load(filename.c_str(), &this->texWidth, &this->texHeight, 0, 4);
    printf("    BMP file read: %s\n", filename.c_str());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texWidth, this->texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image);

    glBindTexture(GL_TEXTURE_2D, 0);

    printf("Successfully read texture from file.\n");

    return 0;
}

/*
 * Generates texture from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::generateTexture() {

    // Read texture from file
    printf("\nStart texture generation.");
    Texture::readTexture();
    printf("Successfully completed texture generation.\n");

    return 0;
}
