/**
 * Wood.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of Perlin noise with perturbation for wood effects.
 */

#include "Wood.h"

Wood::Wood() {
    perlinSource = new Perlin();
}

Wood::~Wood() {
    delete perlinSource;
}

/*
 * Generates a modified Perlin noise value for wood effects.
 *
 * Returns:
 *      float: Perlin noise value
 */
float Wood::noise(float sample_x, float sample_y, float sample_z) {

    float perlinNoise = perlinSource->noise(sample_x, sample_y, sample_z);

    glm::vec2 position = glm::vec2(sample_x, sample_y) * 0.1f;
    position += glm::vec2(10.0f, 10.0f);
    float noise = (float) sqrt((position.x * position.x) + (position.y * position.y));

    return glm::fract(perlinNoise * noise);
}

/*
 * Sets hashing mechanism.
 */
void Wood::setPairingFunction(int pairingFunction) {
    this->perlinSource->setPairingFunction(pairingFunction);
}





