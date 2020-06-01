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
    this->numCells = 20;
    this->cellPoints = new glm::vec2[this->numCells];

    for (int i = 0; i < this->numCells; i++) {
        this->cellPoints[i].x = (float(rand()) / (RAND_MAX)) * 4.0f;
        this->cellPoints[i].y = (float(rand()) / (RAND_MAX)) * 4.0f;
    }

    this->maxDistance = sqrt(pow(-2.0f - 2.0f, 2) + pow(-2.0f - 2.0f, 2));

    float divide = 0.85f;
    this->a = (float(rand()) / (RAND_MAX)) * divide;
    this->d = divide - this->a;
    this->b = (float(rand()) / (RAND_MAX)) * (1.0f - divide);
    this->c = (1.0f - divide) - this->b;

    // Permutation and Gradient tables
    this->permTable = new int[this->numCells];
    this->gradientX = new float[this->numCells];
    this->gradientY = new float[this->numCells];
    this->gradientZ = new float[this->numCells];

    // Initialize Permutation table
    for (int i = 0; i < this->numCells; i++) {
        this->permTable[i] = i;
    }

    // Randomize Permutation table
    for (int i = 0; i < this->numCells; i++) {
        int swapIndex = rand() % this->numCells;

        int temp = this->permTable[i];
        this->permTable[i] = this->permTable[swapIndex];
        this->permTable[swapIndex] = temp;
    }

    // Initialize Gradient table
    for (int i = 0; i < this->numCells; i++) {
        gradientX[i] = (float(rand()) / (RAND_MAX));
        gradientY[i] = (float(rand()) / (RAND_MAX));
        gradientZ[i] = (float(rand()) / (RAND_MAX));
    }

    // Debug
    //printf("    Randomized Covariance Matrix: a: %f | b: %f | c: %f | d: %f | divide: %f\n", this->a, this->b, this->c, this->d, divide);
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
 * Calculates the distance between two 2-dimensional vectors.
 *
 * Returns:
 *      float: distance between two vectors
 */
float Worley::mahalanobisDistance(glm::vec2 fromPoint, glm::vec2 toPoint) {

    // Vector
    glm::vec2 xy = toPoint - fromPoint;

    // Random Covariate Matrix [S0]
    glm::mat2 S = glm::mat2(this->a, this->c, this->b, this->d);
    //glm::mat2 S = glm::mat2(1.0f, 1.0f, 1.0f, 1.0f);                        // Identity (equals Euclidean distance) [S1]

    glm::vec2 dSquared = (xy / S) * xy;

    //float tempSinValue = (float) sin(dSquared.x + dSquared.y);              // [M0]
    //return pow(cos(3.14159f * tempSinValue / 2.0f), 0.5f);                  // [M0]

    //float tempCosValue = (float) cos(dSquared.x + dSquared.y);              // [M2]
    //return pow(sin(3.14159f * tempCosValue / 2.0f), 0.5f);                  // [M2]

    return sqrt(abs(dSquared.x + dSquared.y));                // [M1]
}

/*
 * Generates a Worley noise value.
 *
 * Returns:
 *      float: Worley noise value
 */
float Worley::noise(float sample_x, float sample_y, float sample_z) {

    /// Worley Noise
    glm::vec2 st = glm::vec2(sample_x, sample_y);
    glm::vec2 rand = glm::vec2(0.5f + sin(sample_x * sample_y) * 0.5f);

    /// Nth closest point
    float minDist = this->maxDistance;
    float secondMinDist = this->maxDistance;
    float thirdMinDist = this->maxDistance;
    float maxDist = -999999.0f;
    float secondMaxDist = -999999.0f;
    float thirdMaxDist = -999999.0f;

    int minDistIndex = 0;
    int secondMinDistIndex = 0;
    int thirdMinDistIndex = 0;
    int maxDistIndex = 0;
    int secondMaxDistIndex = 0;
    int thirdMaxDistIndex = 0;


    for (int i = 0; i < this->numCells; i++) {

        // Get current distance
        float ed = distance(st, cellPoints[i]);
        float md = manhattanDistance(st, cellPoints[i]);
        float cd = chebyshevDistance(st, cellPoints[i]);
        float mhd = mahalanobisDistance(st, cellPoints[i]);

        //float currDistance = mhd;
        float currDistance = (cd + ed + md + mhd) / 4.0f;
        //float currDistance = ed;

        if (currDistance < minDist) {
            thirdMinDist = secondMinDist;
            secondMinDist = minDist;
            minDist = currDistance;

            thirdMinDistIndex = secondMinDistIndex;
            secondMinDistIndex = minDistIndex;
            minDistIndex = i;
        } else if (currDistance < secondMinDist) {
            thirdMinDist = secondMinDist;
            secondMinDist = currDistance;

            thirdMinDistIndex = secondMinDistIndex;
            secondMinDistIndex = i;
        } else if (currDistance < thirdMinDist) {
            thirdMinDist = currDistance;

            thirdMinDistIndex = i;
        }

        if (currDistance > maxDist) {
            thirdMaxDist = secondMaxDist;
            secondMaxDist = maxDist;
            maxDist = currDistance;

            thirdMaxDistIndex = secondMaxDistIndex;
            secondMaxDistIndex = maxDistIndex;
            maxDistIndex = i;
        } else if (currDistance > secondMaxDist) {
            thirdMaxDist = secondMaxDist;
            secondMaxDist = currDistance;

            thirdMaxDistIndex = secondMaxDistIndex;
            secondMaxDistIndex = i;
        } else if (currDistance > thirdMaxDist) {
            thirdMaxDist = currDistance;

            thirdMaxDistIndex = i;
        }
    }

    int indexMin = this->permTable[minDistIndex];
    int indexSecondMin = this->permTable[secondMinDistIndex];
    int indexThirdMin = this->permTable[thirdMinDistIndex];
    int indexMax = this->permTable[maxDistIndex];
    int indexSecondMax = this->permTable[secondMaxDistIndex];
    int indexThirdMax = this->permTable[thirdMaxDistIndex];

    // Gradient lookup
    //return sqrt(minDist * gradientX[indexMin]);                                       // [type 2 - mhd]
    //return sqrt(st.x * gradientX[indexMin] + st.y * gradientY[indexMin]);       // [type 1 - mhd]
    //return sqrt(st.x * st.x + st.y * st.y);

    // First closest point
    //return sqrt(minDist);

    // Second closest point
    //return sqrt(secondMinDist);

    // Second-First closest point
    //return 1.0f - sqrt(secondMinDist - minDist);

    // Third closest point
    //return sqrt(thirdMinDist);
    //return 1.0f - sqrt(thirdMinDist);

    // Average of three closest points
    //return (sqrt(minDist) + sqrt(secondMinDist) + sqrt(thirdMinDist)) / 3.0f;
    return 1.0f - (sqrt(minDist) + sqrt(secondMinDist) + sqrt(thirdMinDist)) / 3.0f;
}
