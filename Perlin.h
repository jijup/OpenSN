/**
 * Perlin.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 * 
 * A Perlin noise implementation.
 */

#include <cstdlib>
#include <ctime>
#include <cmath>

#ifndef _PERLIN_H_
#define _PERLIN_H_

class Perlin {
public:
	Perlin();
	~Perlin();

	// Interpolates value
	float lerp(float x);

	// Generates a Perlin noise value, given some 3D coordinates (X, Y, Z).
	float noise(float sample_x, float sample_y, float sample_z);

private:
	// Permutation table
	int *permutationTable; 
	
	// Gradient vectors
	float *gradientX;
	float *gradientY;
	float *gradientZ;
};

#endif
