/**
 * Wavelet.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A Wavelet noise implementation.
 *
 * Implementation heavily based on "Wavelet Noise" by Cook & DeRose.
 *
 * Reference: https://graphics.pixar.com/library/WaveletNoise/paper.pdf
 */

#include "../HashFunctions.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <glm/glm/glm.hpp>

#ifndef _WAVELET_H_
#define _WAVELET_H_

class Wavelet {
public:
    Wavelet();
    ~Wavelet();

    // Generates a Wavelet noise value, given some 3D coordinates (X, Y, Z).
    float noise(float sample_x, float sample_y, float sample_z);

    void downsample(float *from, float *to, int n, int stride);
    void upsample( float *from, float *to, int n, int stride);
    void generateNoiseTile( int n, int olap);
    int mod(int x, int n);

    // Generates a projected Wavelet noise value, given some 3D coordinates (X, Y, Z).
    float projectedNoise(float sample_x, float sample_y, float sample_z);

    float *noiseTileData;
    int noiseTileSize;
};

#endif