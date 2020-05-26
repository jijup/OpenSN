/**
 * Gabor.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of Gabor noise.
 *
 * Heavily based on the SIGGRAPH paper "Procedural Noise using Sparse Gabor Convolution" from Ares Lageo,
 * Sylvain Lefebvre, George Drettakis, Philip Dutre, Katholieke Universiteit Leuven and REVES/INRIA Sophia-Antipolis.
 *
 * Reference: http://graphics.cs.kuleuven.be/publications/LLDD09PNSGC/
 */

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
#include <iostream>

#ifndef _GABOR_H_
#define _GABOR_H_

class Gabor {
public:
    Gabor();
    ~Gabor();

    float gabor(float K, float a, float F_0, float omega_0, float x, float y);

    unsigned morton(unsigned x, unsigned y);

    float cell(int i, int j, float x, float y);

    float helper(float x, float y);

    float variance();

    float noise(float xCoord, float yCoord, float zCoord);

private:
    float K_;                       // Magnitude of Gaussian envelope (amplitude)
    float a_;                       // Weight of Gaussian envelope (amplitude)
    float F_0_;                     // Magnitude of Frequency
    float omega_0_;                 // Orientation of Frequency
    float kernel_radius_;           // Kernel Radius
    float impulse_density_;         // Impulse Density
    unsigned period_;               // Period
    unsigned random_offset_;        // Offset (chosen at random)
};


/*
 * Random number generator.
 */
class pseudo_random_number_generator {
public:
    void seed(unsigned s) {
        x_ = s;
    }

    unsigned operator()() {
        x_ *= 3039177861u; return x_;
    }

    float uniform_0_1() {
        return float(operator()()) / float(UINT_MAX);
    }

    float uniform(float min, float max) {
        return min + (uniform_0_1() * (max - min));
    }

    unsigned poisson(float mean) {
        float g_ = std::exp(-mean);
        unsigned em = 0;

        double t = uniform_0_1();
        while (t > g_) {
            ++em;
            t *= uniform_0_1();
        }

        return em;
    }

private:
    unsigned x_;
};

#endif

