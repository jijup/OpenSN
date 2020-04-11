/**
 * Marble.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementations for various texture perturbations.
 */

#include "Marble.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Marble::Marble() {
    perlinSource = new Perlin();
}

Marble::~Marble() {
    delete perlinSource;

}

/**
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

    float x = xCoord - (int)xCoord;
    float y = yCoord - (int)yCoord;
    float z = zCoord - (int)zCoord;

    float noiseValue = 0;
    float divisor = noiseValue;
    float persistence = 0.50;
    float frequency = 1;
    float amplitude = 2;

    // Turbulence iterations
    int turbulenceIter = 1;
    for (int i = 0; i < turbulenceIter; i++)
    {
        noiseValue += perlinSource->noise(xCoord * frequency, yCoord * frequency, zCoord * frequency) * amplitude;
        divisor += amplitude;
        frequency *= 2.0f;
        amplitude *= persistence;
    }
    noiseValue /= divisor;

    float width = 1000;
    float height = 1000;
    float turbulencePower = 8;
    float turbulenceSize = 128;

    while (turbulenceSize >= 1) {
        noiseValue += perlinSource->noise(xCoord * frequency, yCoord * frequency, zCoord * frequency) * turbulenceSize;
        divisor += amplitude;
        frequency *= 2.0f;
        amplitude *= persistence;
        turbulenceSize /= 2.0;
    }
    noiseValue /= divisor;
    noiseValue = fabs(noiseValue);

    float intermediateNoise = xCoord / width + yCoord / height + turbulencePower*noiseValue / 256;

    float newNoise = fabs(sin(intermediateNoise * 3.14159265358979));

    return newNoise;

}



