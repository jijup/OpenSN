/**
 * Marble.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of a marble texture perturbation.
 */

#include "Perlin.h"
#include <cmath>
#include <iostream>

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

