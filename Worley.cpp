/**
 * Worley.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of Worley noise.
 */

#include "Worley.h"

Worley::Worley() {
    srand(time(NULL));

    this->maxCells = 100;
    this->numCells = rand() % this->maxCells;
    printf("    %d cells being generated.\n", this->numCells);
    this->cellPoints  = new glm::vec2[this->numCells];

    for (int i = 0; i < this->numCells; i++) {
        this->cellPoints[i].x = (float(rand()) / (RAND_MAX)) * 4.0f;
        this->cellPoints[i].y = (float(rand()) / (RAND_MAX)) * 4.0f;
    }

    this->maxDistance = sqrt(pow(-2.0f - 2.0f, 2) + pow(-2.0f - 2.0f, 2));
}

Worley::~Worley() {}

/*
 * Determines the minimum of two floats.
 *
 * Returns:
 *      float: minimum of two floats
 */
float Worley::minimum(float X1, float X2) {
    if (X1 > X2) {
        return X2;
    } else {
        return X1;
    }
}

/*
 * Calculates the distance between two 2-dimensional vectors.
 *
 * Returns:
 *      float: distance between two vectors
 */
float Worley::distance(glm::vec2 fromPoint, glm::vec2 toPoint) {
    return sqrt(pow(fromPoint.x - toPoint.x, 2) + pow(fromPoint.y - toPoint.y, 2));
}

/*
 * Generates a Worley noise value.
 *
 * Returns:
 *      float: Worley noise value
 */
float Worley::noise(float sample_x, float sample_y, float sample_z) {
    glm::vec2 st = glm::vec2(sample_x, sample_y);
    float minimumDistance = this->maxDistance;
    float result;

    for (int i = 0; i < this->numCells; i++) {
        float tempDistance = distance(st, cellPoints[i]);

        minimumDistance = minimum(tempDistance, minimumDistance);
    }

    return sqrt(minimumDistance);

    // Original function (square taken to shift amplitude to a mean of 0.5)
    //return minimumDistance;
}





