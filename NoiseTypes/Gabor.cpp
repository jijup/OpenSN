/**
 * Gabor.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of Gabor noise.
 *
 * Heavily based on the SIGGRAPH paper "Procedural Noise using Sparse Gabor Convolution" from Ares Lageo,
 * Sylvain Lefebvre, George Drettakis, Philip Dutre, Katholieke Universiteit Leuven and REVES/INRIA Sophia-Antipolis.
 *
 * Reference: http://graphics.cs.kuleuven.be/publications/LLDD09PNSGC/
 */

#include "Gabor.h"

Gabor::Gabor() {

    // Rock like texture: with number_of_impulses_per_current at 64 and with 4-8 octaves  (in Fractal)
    //K_ = 16.0; a_ = 2.0; F_0_ = 2.0;

    // Water like texture: with number_of_impulses_per_current at 64 and with 4-8 octaves (in Fractal)
    K_ = 16.0; a_ = 16.0; F_0_ = 16.0;

    omega_0_ = M_PI / 4.0;

    kernel_radius_ = std::sqrt(-std::log(0.05) / M_PI) / a_;

    float number_of_impulses_per_kernel = 64.0;
    impulse_density_ = number_of_impulses_per_kernel / (M_PI * kernel_radius_ * kernel_radius_);

    period_ = 256;
    random_offset_ = std::time(0);
}

Gabor::~Gabor() {}


float Gabor::gabor(float K, float a, float F_0, float omega_0, float x, float y)
{
    float gaussian_envelop = K * std::exp(-M_PI * (a * a) * ((x * x) + (y * y)));
    float sinusoidal_carrier = std::cos(2.0 * M_PI * F_0 * ((x * std::cos(omega_0)) + (y * std::sin(omega_0))));
    return gaussian_envelop * sinusoidal_carrier;
}

unsigned Gabor::morton(unsigned x, unsigned y)
{
    unsigned z = 0;
    for (unsigned i = 0; i < (sizeof(unsigned) * CHAR_BIT); ++i) {
        z |= ((x & (1 << i)) << i) | ((y & (1 << i)) << (i + 1));
    }
    return z;
}

float Gabor::cell(int i, int j, float x, float y) {

    // Periodic vs nonpreiodic Gabor noise implementations
    //unsigned s = (((unsigned(j) % period_) * period_) + (unsigned(i) % period_)) + random_offset_; // periodic noise
    unsigned s = Gabor::morton(i, j) + random_offset_; // nonperiodic noise

    if (s == 0) {
        s = 1;
    }

    // Seed random number generator
    pseudo_random_number_generator prng;
    prng.seed(s);

    // Initialize impulses
    double number_of_impulses_per_cell = impulse_density_ * kernel_radius_ * kernel_radius_;
    unsigned number_of_impulses = prng.poisson(number_of_impulses_per_cell);

    float noise = 0.0;
    for (unsigned i = 0; i < number_of_impulses; ++i) {

        float x_i = prng.uniform_0_1();
        float y_i = prng.uniform_0_1();
        float w_i = prng.uniform(-1.0, +1.0);
        float omega_0_i = prng.uniform(0.0, 2.0 * M_PI);

        float x_i_x = x - x_i;
        float y_i_y = y - y_i;

        if (((x_i_x * x_i_x) + (y_i_y * y_i_y)) < 1.0) {
            // Ansiotropic vs isotropic implementations
            noise += w_i * Gabor::gabor(K_, a_, F_0_, omega_0_, x_i_x * kernel_radius_, y_i_y * kernel_radius_); // anisotropic
            //noise += w_i * Gabor::gabor(K_, a_, F_0_, omega_0_i, x_i_x * kernel_radius_, y_i_y * kernel_radius_); // isotropic
        }
    }

    return noise;
}

float Gabor::helper(float x, float y)  {
    x /= kernel_radius_;
    y /= kernel_radius_;

    float int_x = std::floor(x);
    float int_y = std::floor(y);
    float frac_x = x - int_x;
    float frac_y = y - int_y;
    int i = int(int_x);
    int j = int(int_y);

    float noise = 0.0;
    for (int di = -1; di <= +1; ++di) {
        for (int dj = -1; dj <= +1; ++dj) {
            noise += cell(i + di, j + dj, frac_x - di, frac_y - dj);
        }
    }

    return noise;
}

float Gabor::variance()  {
    float integral_gabor_filter_squared = ((K_ * K_) / (4.0 * a_ * a_)) * (1.0 + std::exp(-(2.0 * M_PI * F_0_ * F_0_) / (a_ * a_)));
    return impulse_density_ * (1.0 / 3.0) * integral_gabor_filter_squared;
}

float Gabor::noise(float xCoord, float yCoord, float zCoord) {

    xCoord /= kernel_radius_;
    yCoord /= kernel_radius_;
    float int_x = std::floor(xCoord);
    float int_y = std::floor(yCoord);
    float frac_x = xCoord - int_x;
    float frac_y = yCoord - int_y;
    int i = int(int_x);
    int j = int(int_y);

    float val = 0.0f;
    for (int di = -1; di <= +1; ++di) {
        for (int dj = -1; dj <= +1; ++dj) {
            val += cell(i + di, j + dj, frac_x - di, frac_y - dj);
        }
    }

    float scale = 3.0 * std::sqrt(variance());
    float x = (float(xCoord) + 0.5) - (float(1000) / 2.0);
    float y = (float(1000 - yCoord - 1) + 0.5) - (float(1000) / 2.0);
    val = 0.5 + (0.5 * (val / scale));

    return val;
}










