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

    int numBaseCurves = 4;
    this->numCurves = 4;
    this->bezierCurves = new glm::vec2*[this->numCurves + numBaseCurves];

    for (int i = 0; i < this->numCurves; i++) {

        // Create array for 4 point of each Bezier curve
        this->bezierCurves[i] = new glm::vec2[4];

        for (int j = 0; j < 4; j++) {
            this->bezierCurves[i][j].x = (float(rand()) / (RAND_MAX)) * 4.0f;
            this->bezierCurves[i][j].y = (float(rand()) / (RAND_MAX)) * 4.0f;
        }
    }

    /// Setup base curves
    glm::vec2 baseCurves[4][4];

    // Right
    /*baseCurves[0][0] = glm::vec2(1.0f, 0.0f) * 4.0f;
    baseCurves[0][1] = glm::vec2(1.0f, 0.33f) * 4.0f;
    baseCurves[0][2] = glm::vec2(1.0f, 0.67f) * 4.0f;
    baseCurves[0][3] = glm::vec2(1.0f, 1.0f) * 4.0f;*/

    // Top right
    baseCurves[0][0] = glm::vec2(0.5f, 1.0f) * 4.0f;
    baseCurves[0][1] = glm::vec2(0.67f, 0.83f) * 4.0f;
    baseCurves[0][2] = glm::vec2(0.83f, 0.67f) * 4.0f;
    baseCurves[0][3] = glm::vec2(1.0f, 0.5f) * 4.0f;

    this->bezierCurves[this->numCurves] = new glm::vec2[4];
    this->bezierCurves[this->numCurves][0].x = baseCurves[0][0].x;
    this->bezierCurves[this->numCurves][0].y = baseCurves[0][0].y;
    this->bezierCurves[this->numCurves][1].x = baseCurves[0][1].x;
    this->bezierCurves[this->numCurves][1].y = baseCurves[0][1].y;
    this->bezierCurves[this->numCurves][2].x = baseCurves[0][2].x;
    this->bezierCurves[this->numCurves][2].y = baseCurves[0][2].y;
    this->bezierCurves[this->numCurves][3].x = baseCurves[0][3].x;
    this->bezierCurves[this->numCurves][3].y = baseCurves[0][3].y;

    // Left
    /*baseCurves[1][0] = glm::vec2(0.0f, 0.0f) * 4.0f;
    baseCurves[1][1] = glm::vec2(0.0f, 0.33f) * 4.0f;
    baseCurves[1][2] = glm::vec2(0.0f, 0.67f) * 4.0f;
    baseCurves[1][3] = glm::vec2(0.0f, 1.0f) * 4.0f;*/

    // Top left
    baseCurves[1][0] = glm::vec2(0.0f, 0.5f) * 4.0f;
    baseCurves[1][1] = glm::vec2(0.17f, 0.67f) * 4.0f;
    baseCurves[1][2] = glm::vec2(0.33f, 0.83f) * 4.0f;
    baseCurves[1][3] = glm::vec2(0.5f, 1.0f) * 4.0f;

    this->bezierCurves[this->numCurves + 1] = new glm::vec2[4];
    this->bezierCurves[this->numCurves + 1][0].x = baseCurves[1][0].x;
    this->bezierCurves[this->numCurves + 1][0].y = baseCurves[1][0].y;
    this->bezierCurves[this->numCurves + 1][1].x = baseCurves[1][1].x;
    this->bezierCurves[this->numCurves + 1][1].y = baseCurves[1][1].y;
    this->bezierCurves[this->numCurves + 1][2].x = baseCurves[1][2].x;
    this->bezierCurves[this->numCurves + 1][2].y = baseCurves[1][2].y;
    this->bezierCurves[this->numCurves + 1][3].x = baseCurves[1][3].x;
    this->bezierCurves[this->numCurves + 1][3].y = baseCurves[1][3].y;

    // Bottom
    /*baseCurves[2][0] = glm::vec2(0.0f, 0.0f) * 4.0f;
    baseCurves[2][1] = glm::vec2(0.33f, 0.0f) * 4.0f;
    baseCurves[2][2] = glm::vec2(0.67f, 0.0f) * 4.0f;
    baseCurves[2][3] = glm::vec2(1.0f, 0.0f) * 4.0f;*/

    // Bottom right
    baseCurves[2][0] = glm::vec2(0.5f, 0.0f) * 4.0f;
    baseCurves[2][1] = glm::vec2(0.67f, 0.17f) * 4.0f;
    baseCurves[2][2] = glm::vec2(0.83f, 0.33f) * 4.0f;
    baseCurves[2][3] = glm::vec2(1.0f, 0.5f) * 4.0f;

    this->bezierCurves[this->numCurves + 2] = new glm::vec2[4];
    this->bezierCurves[this->numCurves + 2][0].x = baseCurves[2][0].x;
    this->bezierCurves[this->numCurves + 2][0].y = baseCurves[2][0].y;
    this->bezierCurves[this->numCurves + 2][1].x = baseCurves[2][1].x;
    this->bezierCurves[this->numCurves + 2][1].y = baseCurves[2][1].y;
    this->bezierCurves[this->numCurves + 2][2].x = baseCurves[2][2].x;
    this->bezierCurves[this->numCurves + 2][2].y = baseCurves[2][2].y;
    this->bezierCurves[this->numCurves + 2][3].x = baseCurves[2][3].x;
    this->bezierCurves[this->numCurves + 2][3].y = baseCurves[2][3].y;

    // Top
    /*baseCurves[3][0] = glm::vec2(0.0f, 1.0f) * 4.0f;
    baseCurves[3][1] = glm::vec2(0.33f, 1.0f) * 4.0f;
    baseCurves[3][2] = glm::vec2(0.67f, 1.0f) * 4.0f;
    baseCurves[3][3] = glm::vec2(1.0f, 1.0f) * 4.0f;*/

    // Bottom left
    baseCurves[3][0] = glm::vec2(0.0f, 0.5f) * 4.0f;
    baseCurves[3][1] = glm::vec2(0.17f, 0.33f) * 4.0f;
    baseCurves[3][2] = glm::vec2(0.33f, 0.17f) * 4.0f;
    baseCurves[3][3] = glm::vec2(0.5f, 0.0f) * 4.0f;

    this->bezierCurves[this->numCurves + 3] = new glm::vec2[4];
    this->bezierCurves[this->numCurves + 3][0].x = baseCurves[3][0].x;
    this->bezierCurves[this->numCurves + 3][0].y = baseCurves[3][0].y;
    this->bezierCurves[this->numCurves + 3][1].x = baseCurves[3][1].x;
    this->bezierCurves[this->numCurves + 3][1].y = baseCurves[3][1].y;
    this->bezierCurves[this->numCurves + 3][2].x = baseCurves[3][2].x;
    this->bezierCurves[this->numCurves + 3][2].y = baseCurves[3][2].y;
    this->bezierCurves[this->numCurves + 3][3].x = baseCurves[3][3].x;
    this->bezierCurves[this->numCurves + 3][3].y = baseCurves[3][3].y;

    this->numCurves += 4;

    this->maxDistance = 999999.0f;

    float divide = 0.85f;
    this->a = (float(rand()) / (RAND_MAX)) * divide;
    this->d = divide - this->a;
    this->b = (float(rand()) / (RAND_MAX)) * (1.0f - divide);
    this->c = (1.0f - divide) - this->b;
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
    //glm::vec2 currentMinimumVec;

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
        /*if (tempDistance < currentMinimum) {
            currentMinimum = tempDistance;
            currentMinimumVec = glm::vec2(x, y);
        }*/
        currentMinimum = minimum(tempDistance, currentMinimum);

        t += interval;
    }

    /*glm::vec2 result = glm::cross(glm::vec3(fromPoint.x, fromPoint.y, 0.0f), glm::vec3(currentMinimumVec.x, currentMinimumVec.y, 0.0f));
    return glm::dot(result.x, result.y);*/

    return currentMinimum;
}

/*
 * Calculates the Manhattan distance between a 2-dimensional vector and a Bezier curve.
 *
 * Returns:
 *      float: distance between two vectors
 */
float ExperimentalNoise::manhattanDistance(glm::vec2 fromPoint, glm::vec2 *toCurve, float interval) {

    float currentMinimum = 999999.0f;
    //glm::vec2 currentMinimumVec;

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
        float tempDistance = fabs(fromPoint.x - x) + fabs(fromPoint.y - y);

        // Check if distance is less than previous minimum
        /*if (tempDistance < currentMinimum) {
            currentMinimum = tempDistance;
            currentMinimumVec = glm::vec2(x, y);
        }*/
        currentMinimum = minimum(tempDistance, currentMinimum);

        t += interval;
    }

    /*glm::vec2 result = glm::cross(glm::vec3(fromPoint.x, fromPoint.y, 0.0f), glm::vec3(currentMinimumVec.x, currentMinimumVec.y, 0.0f));
    return glm::dot(result.x, result.y);*/

    return currentMinimum;
}

/*
 * Calculates the Chebyshev distance between a 2-dimensional vector and a Bezier curve.
 *
 * Returns:
 *      float: distance between two vectors
 */
float ExperimentalNoise::chebyshevDistance(glm::vec2 fromPoint, glm::vec2 *toCurve, float interval) {

    float currentMinimum = 999999.0f;
    //glm::vec2 currentMinimumVec;

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
        float tempDistance = fmax(fabs(fromPoint.x - x), fabs(fromPoint.y - y));

        // Check if distance is less than previous minimum
        /*if (tempDistance < currentMinimum) {
            currentMinimum = tempDistance;
            currentMinimumVec = glm::vec2(x, y);
        }*/
        currentMinimum = minimum(tempDistance, currentMinimum);

        t += interval;
    }

    /*glm::vec2 result = glm::cross(glm::vec3(fromPoint.x, fromPoint.y, 0.0f), glm::vec3(currentMinimumVec.x, currentMinimumVec.y, 0.0f));
    return glm::dot(result.x, result.y);*/

    return currentMinimum;
}

/*
 * Calculates the distance between two 2-dimensional vectors.
 *
 * Returns:
 *      float: distance between two vectors
 */
float ExperimentalNoise::mahalanobisDistance(glm::vec2 fromPoint, glm::vec2 *toCurve, float interval) {

    float currentMinimum = 999999.0f;
    //glm::vec2 currentMinimumVec;

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
        glm::vec2 xy = glm::vec2(x, y) - fromPoint;
        glm::mat2 S = glm::mat2(this->a, this->c, this->b, this->d);
        glm::vec2 dSquared = (xy / S) * xy;

        //float tempDistance = sqrt(abs(dSquared.x + dSquared.y));
        float tempDistance = (float) sin(dSquared.x + dSquared.y);
        tempDistance = pow(cos(3.14159f * tempDistance / 2.0f), 0.5f);

        currentMinimum = minimum(tempDistance, currentMinimum);

        t += interval;
    }

    return currentMinimum;
}


/*
 * Generates
 *
 */
float ExperimentalNoise::noise(float sample_x, float sample_y, float sample_z) {

    glm::vec2 st = glm::vec2(sample_x, sample_y);
    float minDist = this->maxDistance;
    float secondMinDist = this->maxDistance;
    float thirdMinDist = this->maxDistance;

    for (int i = 0; i < this->numCurves; i++) {

        float md = manhattanDistance(st, this->bezierCurves[i], 0.05f);
        float cd = chebyshevDistance(st, this->bezierCurves[i], 0.05f);
        float ed = distance(st, this->bezierCurves[i], 0.05f);
        float mhd = mahalanobisDistance(st, this->bezierCurves[i], 0.05f);

        //float currDistance = ed;                                                    // Cracked (domain warped) or Ridges (domain normal)
        float currDistance = (cd + ed + md) / 3.0f;                                 // Ridges (domain warped or unwarped)
        //float currDistance = ((ed - cd) / (md - cd)) / 2.0f;
        //float currDistance = mhd;
        //float currDistance = (cd + ed + md + mhd) / 4.0f;

        // Get minimum distances to current Bezier curve
        if (currDistance < minDist) {
            thirdMinDist = secondMinDist;
            secondMinDist = minDist;
            minDist = currDistance;
        } else if (currDistance < secondMinDist) {
            thirdMinDist = secondMinDist;
            secondMinDist = currDistance;
        } else if (currDistance < thirdMinDist) {
            thirdMinDist = currDistance;
        }
    }

    // Third closest point
    return 1.0f - sqrt(thirdMinDist);
    //return sqrt(thirdMinDist);

    //return sqrt(secondMinDist - minDist);
    //return 1.0f - sqrt(secondMinDist - minDist);

    // Average of three closest points
    //return 1.0f - (sqrt(minDist) + sqrt(secondMinDist) + sqrt(thirdMinDist)) / 3.0f;
}

/*
 // Combined Perlin and modified Worley noise via Bezier curve generation.
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