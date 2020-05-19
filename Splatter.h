/**
 * Splatter.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of Value noise with perturbation for splatter effects.
 */

#include "Perlin.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <glm/glm/glm.hpp>

#ifndef _SPLATTER_H_
#define _SPLATTER_H_

class Splatter {
public:
    Splatter();
    ~Splatter();

    // Helper function to generate splatter
    float splatter(glm::vec2 st);

    // Generates a Worley noise value between, given some 3D coordinates (X, Y, Z).
    float noise(float sample_x, float sample_y, float sample_z);

    // Sets hashing mechanism
    void setPairingFunction(int pairingFunction);

private:
    Perlin *perlinSource;
    glm::vec2 randA;
    glm::vec2 randB;
};

#endif






