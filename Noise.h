/*
 * Noise.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Driver function for noise generation.
 */

#include "Fractal.h"
#include "HashFunctions.h"
#include <string>
#include <vector>
#include <math.h>

#ifndef _NOISE_H_
#define _NOISE_H_


class Noise {
public:
    Noise();
    ~Noise();

    struct Point {
        int x;
        int y;
        float colour;
    };
    
    // Generates Perlin noise
    std::vector<Noise::Point> generatePerlin(int pairingFunction, int noiseType, int width, int height, int textureType);
    
    // Generates Gabor noise
    std::vector<Noise::Point> generateGabor(int pairingFunction, int noiseType, int width, int height, int textureType);
};

#endif

