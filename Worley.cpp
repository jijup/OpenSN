/**
 * Worley.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of Worley noise.
 */

#include "Worley.h"

Worley::Worley() {
    srand(time(NULL));

    this->maxCells = 90;
    this->numCells = 10 + rand() % this->maxCells;
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
 * Calculates the distance between two 2-dimensional vectors.
 *
 * Returns:
 *      float: distance between two vectors
 */
float Worley::manhattanDistance(glm::vec2 fromPoint, glm::vec2 toPoint) {
    return fabs(fromPoint.x - toPoint.x) + fabs(fromPoint.y - toPoint.y);
}

/*
 * Calculates the distance between two 2-dimensional vectors.
 *
 * Returns:
 *      float: distance between two vectors
 */
float Worley::chebyshevDistance(glm::vec2 fromPoint, glm::vec2 toPoint) {
    return fmax(fabs(fromPoint.x - toPoint.x), fabs(fromPoint.y - toPoint.y));
}

/*
 * Generates a Worley noise value.
 *
 * Returns:
 *      float: Worley noise value
 */
float Worley::noise(float sample_x, float sample_y, float sample_z) {

    glm::vec2 st = glm::vec2(sample_x, sample_y);
    glm::vec2 rand = glm::vec2(0.5f + sin(sample_x * sample_y) * 0.5f);

    /// Nth closest point
    float minDist = this->maxDistance;
    float secondMinDist = this->maxDistance;
    float thirdMinDist = this->maxDistance;

    for (int i = 0; i < this->numCells; i++) {

        // Get current distance
        //float currDistance = distance(st, cellPoints[i]);
        float currDistance = manhattanDistance(st, cellPoints[i]);
        //float currDistance = chebyshevDistance(st, cellPoints[i]);

        if (currDistance < minDist) {
            float tempDistance = minDist;
            minDist = currDistance;
            thirdMinDist = secondMinDist;
            secondMinDist = tempDistance;
        } else if (currDistance < secondMinDist) {
            thirdMinDist = secondMinDist;
            secondMinDist = currDistance;
        } else if (currDistance < thirdMinDist) {
            thirdMinDist = currDistance;
        }
    }

    // First closest point
    return sqrt(minDist);

    // Second closest point
    //return sqrt(secondMinDist);

    // Second-First closest point
    //return sqrt(secondMinDist - minDist);

    // Third closest point
    //return sqrt(thirdMinDist);

    // Average of three closest points
    //return (sqrt(minDist) + sqrt(secondMinDist) + sqrt(thirdMinDist)) / 3.0f;

    // Testing
    //printf("\nminDist: %f", glm::smoothstep(0.0f, 1.0f, sqrt(minDist)));


    /// Moving Points Worley


}
