/**
 * Worley.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of Worley noise.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <glm/glm/glm.hpp>

#ifndef _WORLEY_H_
#define _WORLEY_H_

class Worley {
public:
    Worley();
    ~Worley();

    // Returns the number of cells being generated
    int getNumberOfCells() {
        return this->numCells;
    }

    // Returns the minimum of two parameters
    float minimum(float X1, float X2);

    // Calculate distance to between two points
    float distance(glm::vec2 fromPoint, glm::vec2 toPoint);
    float manhattanDistance(glm::vec2 fromPoint, glm::vec2 toPoint);
    float chebyshevDistance(glm::vec2 fromPoint, glm::vec2 toPoint);

    // Generates a Worley noise value between, given some 3D coordinates (X, Y, Z).
    float noise(float sample_x, float sample_y, float sample_z);

private:
    int maxCells;
    int numCells;
    glm::vec2 *cellPoints;

    float maxDistance;
};

#endif






