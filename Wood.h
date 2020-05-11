/**
 * Wood.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of Perlin noise with perturbation for wood effects.
 */


#include "Perlin.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <glm/glm/glm.hpp>

#ifndef _WOOD_H_
#define _WOOD_H_

class Wood {
public:
    Wood();
    ~Wood();

    // Generates a Perlin noise (with wood perturbation) value between, given some 3D coordinates (X, Y, Z).
    float noise(float sample_x, float sample_y, float sample_z);

private:
    Perlin *perlinSource;
};

#endif






