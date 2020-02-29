/*
 * Perlin.h
 * 
 * A Perlin noise implementation.
 *
 * Author: Sheldon Taylor
 */

#ifndef _PERLIN_H_
#define _PERLIN_H_

class Perlin {
public:
	Perlin();
	~Perlin();

	// Generates a Perlin noise value between [-1, 1], given some 3D coordination (X, Y, Z).
	float noise(float sample_x, float sample_y, float sample_z);

private:
	// Permutation table
	int *p; 
	
	// Gradient vectors
	float *Gx;
	float *Gy;
	float *Gz;
};

#endif
