/**
 * Noise.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Driver function for noise generation.
 */

#include "Fractal.h"
#include "HashFunctions.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <time.h>

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

    struct Point3D {
        int x;
        int y;
        int z;
        float colour;
    };

    // Generates Perlin noise
    std::vector<Noise::Point> generatePerlin(int pairingFunction, int noiseType, int width, int height);

    // Generates Primed Perlin Noise
    std::vector<Noise::Point> generatePrimedGradient(int pairingFunction, int noiseType, int width, int height);
    std::vector<Noise::Point3D> generatePrimedGradient3D(int pairingFunction, int noiseType, int width, int height);

    // Generates Primed Density Noise
    std::vector<Noise::Point> generatePrimedDensity(int pairingFunction, int noiseType, int width, int height);
    
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

    // Generate value noise (wood)
    std::vector<Noise::Point> generateBetterGradient(int pairingFunction, int noiseType, int width, int height);

    // Generate value noise (wood)
    std::vector<Noise::Point> generateWavelet(int pairingFunction, int noiseType, int width, int height);

    // Generate value noise (wood)
    std::vector<Noise::Point> generatePhasor(int pairingFunction, int noiseType, int width, int height);
};

#endif

