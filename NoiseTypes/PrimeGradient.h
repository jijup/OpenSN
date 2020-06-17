/**
 * PrimeGradient.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A gradient noise implementation with prime numbers as gradients.
 */

#include "../HashFunctions.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <glm/glm/glm.hpp>

#ifndef _PRIMEGRADIENT_H_
#define _PRIMEGRADIENT_H_

class PrimeGradient {
public:
    PrimeGradient();
	~PrimeGradient();

    // Sets width and height
    void setDimensions(int width, int height);

    // Sets hashing mechanism
    void setPairingFunction(int pairingFunction);

    // Sets number of octaves
    void setNumOctaves(int numOctaves);

    // Updates current octaves
    void updateCurrentOctave(int currentOctave);

    // Generates prime table
    void generatePrimeTable();

	// Smooth value
	float fade(float x);

	// Interpolate value
	float lerp(float a, float b, float x);

	// Determines if a single value is prime
	bool isPrime(int val);

	// Find all primes up to a certain value
	void sieve(int offset, int numPrimes);

	// Generates a Perlin noise value, given some 3D coordinates (X, Y, Z).
	float noise(float sample_x, float sample_y, float sample_z);

private:
	int width;
	int height;

	HashFunctions hashInstance;
	int pairingFunction;

    int numPrimes, offset;
	int *prime;

	int numOctaves;
	int currentOctave;
};

#endif
