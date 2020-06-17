/**
 * PrimeGradientDensity.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A gradient noise implementation with prime number density as gradients.
 */

#include "../HashFunctions.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <glm/glm/glm.hpp>

///
#include <matplotlib-cpp/matplotlibcpp.h>
namespace plt = matplotlibcpp;
///

#ifndef _PRIMEGRADIENTDENSITY_H_
#define _PRIMEGRADIENTDENSITY_H_

class PrimeGradientDensity {
public:
    PrimeGradientDensity();
    ~PrimeGradientDensity();

    // Sets width and height
    void setDimensions(int width, int height);

    // Sets hashing mechanism
    void setPairingFunction(int pairingFunction);

    // Fade
    float fade(float x);

    // Interpolate
    float lerp(float a, float b, float x);

    // Determines if a single value is prime
    bool isPrime(int val);

    // Generates a Perlin noise value, given some 3D coordinates (X, Y, Z).
    float noise(float sample_x, float sample_y, float sample_z);

private:
    int width;
    int height;

    HashFunctions hashInstance;
    int pairingFunction;

    int offsetX, offsetY;
};

#endif
