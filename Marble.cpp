/**
 * Marble.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of a marble texture perturbation.
 */

#include "Marble.h"

Marble::Marble() {
    perlinSource = new Perlin();
}

Marble::~Marble() {
    delete perlinSource;
}

/*
 * Marble texture perturbation.
 *
 * Parameters:
 *      xCoord: current noise value (prior to Gaussian distribution)
 *      yCoord: pixels in x-dimension
 *      zCoord: pixels in y-dimension
 *
 * Returns:
 *      float: perturbed noise value
 */
float Marble::noise(float xCoord, float yCoord, float zCoord) {

    float noiseValue = 0;
    float divisor = noiseValue;

    // Standard values for noise calculation
    float persistence = 0.50;
    float frequency = 1;
    float amplitude = 2;

    // Octave iteration
    int turbulenceIter = 1;
    for (int i = 0; i < turbulenceIter; i++) {
        noiseValue += perlinSource->noise(xCoord * frequency, yCoord * frequency, zCoord * frequency) * amplitude;
        divisor += amplitude;
        frequency *= 2.0f;
        amplitude *= persistence;
    }
    noiseValue /= divisor;

    // Height and width of image
    // TODO: Pass as parameter
    float width = 1000;
    float height = 1000;

    /// --- Start: Types of marble formations
    // 1. Fine Grained Marble (more efficient)
    //float turbulencePower = 128;
    //float turbulenceSize = 8;

    // 2. Rough Marble (better quality)
    float turbulencePower = 8;
    float turbulenceSize = 128;
    /// --- End: Types of marble formation

    // Perturb iterations
    while (turbulenceSize >= 1) {
        noiseValue += perlinSource->noise(xCoord * frequency, yCoord * frequency, zCoord * frequency) * turbulenceSize;
        divisor += amplitude;
        frequency *= 2.0f;
        amplitude *= persistence;
        turbulenceSize /= 2.0;
    }
    noiseValue /= divisor;

    float tempNoise = xCoord / width + yCoord / height + turbulencePower*fabs(noiseValue) / 256;
    return fabs(sin(tempNoise * 3.14159265358979));
}



