/**
 * ExperimentalNoise.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of new and experimental noises.
 */

#include "ExperimentalNoise.h"

ExperimentalNoise::ExperimentalNoise() {
    this->perlinSource = new Perlin();

    srand(time(NULL));

    this->maxCurves = 5;
    //this->numCurves = rand() % this->maxCurves;
    this->numCurves = 5;
    this->bezierCurves = new glm::vec2*[this->numCurves];
    this->bezierTable = new float[this->numCurves];

    for (int i = 0; i < this->numCurves; i++) {

        // Create array for 4 point of each Bezier curve
        this->bezierCurves[i] = new glm::vec2[4];

        for (int j = 0; j < 4; j++) {
            this->bezierCurves[i][j].x = (float(rand()) / (RAND_MAX)) * 4.0f;
            this->bezierCurves[i][j].y = (float(rand()) / (RAND_MAX)) * 4.0f;
        }
    }

    this->maxDistance = 999999.0f;
}

ExperimentalNoise::~ExperimentalNoise() {}

/*
 * Determines the minimum of two floats.
 *
 * Returns:
 *      float: minimum of two floats
 */
float ExperimentalNoise::minimum(float X1, float X2) {
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
float ExperimentalNoise::distance(glm::vec2 fromPoint, glm::vec2 *toCurve, float interval) {

    float currentMinimum = 999999.0f;

    float t = 0.0f;
    while (t <= 1.0f) {

        // Calculate point on Bezier curve
        float x = (1.0f - t) * (1.0f - t) * (1.0f - t) * toCurve[0].x +
                  3.0f * (1.0f - t) * (1.0f - t) * t * toCurve[1].x +
                  3.0f * (1.0f - t) * t * t * toCurve[2].x +
                  t * t * t * toCurve[3].x;

        float y = (1.0f - t) * (1.0f - t) * (1.0f - t) * toCurve[0].y +
                  3.0f * (1.0f - t) * (1.0f - t) * t * toCurve[1].y +
                  3.0f * (1.0f - t) * t * t * toCurve[2].y +
                  t * t * t * toCurve[3].y;

        // Find distance between point and current Bezier curve point
        float tempDistance = sqrt(pow(fromPoint.x - x, 2) + pow(fromPoint.y - y, 2));

        // Check if distance is less than previous minimum
        currentMinimum = minimum(tempDistance, currentMinimum);

        t += interval;
    }

    return currentMinimum;
}

/*
 *
 *
 */
float ExperimentalNoise::noise(float sample_x, float sample_y, float sample_z) {

    float perlinNoise = perlinSource->noise(sample_x, sample_y, sample_z);

    glm::vec2 st = glm::vec2(sample_x, sample_y);
    float minimumDistance = this->maxDistance;
    float sumDistance = 0.0f;

    for (int i = 0; i < this->numCurves; i++) {

        float tempDistance = distance(st, this->bezierCurves[i], 0.05f);

        minimumDistance = minimum(tempDistance, minimumDistance);
        sumDistance += tempDistance;
    }

    return sqrt(minimumDistance);
    //return minimumDistance;
    //return minimumDistance * perlinNoise;
}

/*
 // Combined Perlin noise and a modified Worley noise via Bezier curve generation.
float ExperimentalNoise::noise(float sample_x, float sample_y, float sample_z) {

    float perlinNoise = perlinSource->noise(sample_x, sample_y, sample_z);

    glm::vec2 st = glm::vec2(sample_x, sample_y);
    st *= perlinNoise;
    float minimumDistance = this->maxDistance;

    for (int i = 0; i < this->numCurves; i++) {
        float tempDistance = distance(st, this->bezierCurves[i], 0.05f);

        minimumDistance = minimum(tempDistance, minimumDistance);

    }

    return sqrt(minimumDistance);
}
*/

/*
 * Sets hashing mechanism.
 */
void ExperimentalNoise::setPairingFunction(int pairingFunction) {
    this->perlinSource->setPairingFunction(pairingFunction);
}