/**
 * Noise.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Driver function for noise generation.
 */

#include "Fractal.h"
#include "HashFunctions.h"
#include "Marble.h"
#include <iostream>
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
    std::vector<Noise::Point> generatePerlin(int pairingFunction, int noiseType, int width, int height);
    
    // Generates Gabor noise
    std::vector<Noise::Point> generateGabor(int pairingFunction, int noiseType, int width, int height);

    // Generates Marble noise
    std::vector<Noise::Point> generateMarble(int pairingFunction, int noiseType, int width, int height);

    // Generates Worley noise
    std::vector<Noise::Point> generateWorley(int pairingFunction, int noiseType, int width, int height);

    // Generates ExperimentalNoise noise
    std::vector<Noise::Point> generateExperiental(int pairingFunction, int noiseType, int width, int height);

    // Generate value noise (splatter)
    std::vector<Noise::Point> generateSplatter(int pairingFunction, int noiseType, int width, int height);

    // Generate value noise (wood)
    std::vector<Noise::Point> generateWood(int pairingFunction, int noiseType, int width, int height);
};

#endif

