/**
 * ExperimentalNoise.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of new and experimental noises.
 */

#include "Perlin.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <glm/glm/glm.hpp>

#ifndef _CURL_H_
#define _CURL_H_

class ExperimentalNoise {
public:
    ExperimentalNoise();
    ~ExperimentalNoise();

    // Returns the number of Bezier curves being generated
    int getNumberOfCurves() {
        return this->numCurves;
    }

    // Returns the minimum of two parameters
    float minimum(float X1, float X2);

    // Calculate distance to between two points
    float distance(glm::vec2 fromPoint, glm::vec2 *toCurve, float interval);

    // Generates a ExperimentalNoise noise value between, given some 3D coordinates (X, Y, Z).
    float noise(float sample_x, float sample_y, float sample_z);

    // Sets hashing mechanism
    void setPairingFunction(int pairingFunction);

private:
    int maxCurves;
    int numCurves;
    float maxDistance;

    glm::vec2 **bezierCurves;
    float *bezierTable;

    // FIXME: FOR TESTING
    Perlin *perlinSource;
};

#endif






