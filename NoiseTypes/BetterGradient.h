/**
 * BetterGradient.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A Better Gradient noise implementation.
 *
 * Implementation heavily based on "Better Gradient Noise" by Kensler, Knoll & Shirly
 *
 * Reference: https://sci.utah.edu/publications/SCITechReports/UUSCI-2008-001.pdf
 */

#include "../HashFunctions.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <glm/glm/glm.hpp>

#ifndef _BETTERGRADIENT_H_
#define _BETTERGRADIENT_H_

class BetterGradient {
public:
    BetterGradient();
    ~BetterGradient();

    // Generates a Better Gradient noise value, given some 3D coordinates (X, Y, Z).
    float noise(float sample_x, float sample_y, float sample_z);

private:

    // Gradient vectors
    float *gradientX;
    float *gradientY;
    float *gradientZ;

    int width;
    int height;

    HashFunctions hashInstance;
    int pairingFunction;

    int *permutationTableX;
    int *permutationTableY;
    int *permutationTableZ;
};

#endif
