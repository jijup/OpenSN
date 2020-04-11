/*
 * Texture.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementations for various texture perturbations.
 */

#include "Perlin.h"

#ifndef _MARBLE_H_
#define _MARBLE_H_

class Marble {
public:
    Marble();
    ~Marble();

    // Generates a Marble noise value between [-1, 1], given some 3D coordinates (X, Y, Z)
    float noise(float sample_x, float sample_y, float sample_z);



private:
    Perlin *perlinSource;

};

#endif

