/**
 * Splatter.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of Perlin noise with perturbation for splatter effects.
 */

#include "Splatter.h"

Splatter::Splatter() {
    srand(time(NULL));
    this->randA = glm::vec2(rand() % 500, rand() % 500);
    this->randB = glm::vec2(rand() % 500, rand() % 500);

    perlinSource = new Perlin();
}

Splatter::~Splatter() {
    delete perlinSource;
}

/*
 * Helper function to generate splatter effect.
 *
 * Returns:
 *      vec2: 2D Vector of interpolated values
 */
float Splatter::splatter(glm::vec2 st) {
    glm::vec2 i = glm::floor(st);
    glm::vec2 f = glm::fract(st);
    glm::vec2 u = f * f * (3.0f - (2.0f * f));

    // [00] random step
    glm::vec2 randi00 = i + glm::vec2(0.0f, 0.0f);
    glm::vec2 randf00 = f - glm::vec2(0.0f, 0.0f);

    glm::vec2 tempi00 = glm::vec2(glm::dot(randi00,this->randA), glm::dot(randi00,this->randB));
    glm::vec2 incri00 = 2.0f * glm::fract(glm::sin(tempi00) * 43758.5453123f) - 1.0f;

    float dot00 = glm::dot(incri00, randf00);

    // [10] random step
    glm::vec2 randi10 = i + glm::vec2(1.0f, 0.0f);
    glm::vec2 randf10 = f - glm::vec2(1.0f, 0.0f);

    glm::vec2 tempi10 = glm::vec2(glm::dot(randi10,this->randA), glm::dot(randi10,this->randB));
    glm::vec2 incri10 = 2.0f * glm::fract(glm::sin(tempi10) * 43758.5453123f) - 1.0f;

    float dot10 = glm::dot(incri10, randf10);

    // [01] random step
    glm::vec2 randi01 = i + glm::vec2(0.0f, 1.0f);
    glm::vec2 randf01 = f - glm::vec2(0.0f, 1.0f);

    glm::vec2 tempi01 = glm::vec2(glm::dot(randi01,this->randA), glm::dot(randi01,this->randB));
    glm::vec2 incri01 = 2.0f * glm::fract(glm::sin(tempi01) * 43758.5453123f) - 1.0f;

    float dot01 = glm::dot(incri01, randf01);

    // [11] random step
    glm::vec2 randi11 = i + glm::vec2(1.0f, 1.0f);
    glm::vec2 randf11 = f - glm::vec2(1.0f, 1.0f);

    glm::vec2 tempi11 = glm::vec2(glm::dot(randi11,this->randA), glm::dot(randi11,this->randB));
    glm::vec2 incri11 = 2.0f * glm::fract(glm::sin(tempi11) * 43758.5453123f) - 1.0f;

    float dot11 = glm::dot(incri11, randf11);

    // Interpolation step
    float lerpX1 = glm::mix(dot00, dot10, u.x);
    float lerpX2 = glm::mix(dot01, dot11, u.x);
    float lerpY = glm::mix(lerpX1, lerpX2, u.y);

    return lerpY;
}

/*
 * Generates a modified Perlin noise value for splatter effects.
 *
 * Returns:
 *      float: Value noise value
 */
float Splatter::noise(float sample_x, float sample_y, float sample_z) {

    glm::vec2 st = glm::vec2(sample_x, sample_y);
    float perlinNoise = perlinSource->noise(sample_x, sample_y, sample_z);
    perlinNoise = 1.0f - (float)(glm::pow(glm::min(glm::cos(3.14159f * perlinNoise / 2.0f), 1.0f - glm::abs(perlinNoise)), 3.5f));

    float dist = (float) sqrt((st.x * st.x) + (st.y * st.y)) / 4.0f;

    st += Splatter::splatter(st * dist) + perlinNoise;
    float noise = glm::smoothstep(-0.2f, -0.18f, Splatter::splatter(st));
    noise -= glm::smoothstep(0.25f, 0.3f, Splatter::splatter(st * 5.0f));
    noise += glm::smoothstep(0.5f, 0.75f, Splatter::splatter(st * 5.0f));

    return glm::smoothstep(0.0f, 0.02f, noise);
}

/*
 * Sets hashing mechanism.
 */
void Splatter::setPairingFunction(int pairingFunction) {
    this->perlinSource->setPairingFunction(pairingFunction);
}





