/**
 * Phasor.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A Phasor noise implementation.
 *
 * Implementation heavily based on "Procedural Phasor Noise" by Tricard, Efremov, Zanni, Neyret, Martinez, Lefebvre.
 *
 * Reference: https://dl.acm.org/doi/pdf/10.1145/3306346.3322990?download=true
 */

#include "../HashFunctions.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <glm/glm/glm.hpp>

#ifndef _PHASOR_H_
#define _PHASOR_H_

class Phasor {
public:
    Phasor();
    ~Phasor();

    // Generates a Phasor noise value, given some 3D coordinates (X, Y, Z).
    float noise(float sample_x, float sample_y, float sample_z);

    glm::vec2 phasor(glm::vec2 x, float f, float b, float o, float phi);
    int morton(int x, int y);
    void init_noise();
    glm::vec2 cell(glm::ivec2 ij, glm::vec2 uv, float f, float b);
    glm::vec2 eval_noise(glm::vec2 uv, float f, float b);
    float PWM(float x, float r);
    float square(float x);
    float sawTooth(float x);

    int width = 1000;
    int height = 1000;

    //phasor noise parameters
    float _f = 50.0;
    float _b = 32.0;
    float _o = 1.0;
    float _kr;
    int _impPerKernel = 32;
    int _seed = 1;
    glm::vec2 uv;

    // PRNG
    int N = 15487469;
    int x_;
    void seed(int s){x_ = s;}
    int next() { x_ *= 3039177861; x_ = x_ % N;return x_; }
    float uni_0_1() {return  float(next()) / float(N);}
    float uni(float min, float max){ return min + (uni_0_1() * (max - min));}
    //float uni(float min, float max){ return min + ((rand() / RAND_MAX * 2.0f * M_PI) * (max - min));}
};

#endif