/**
 * Perlin.cpp
 *
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 */

#include "Perlin.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Perlin::Perlin() {
	srand(time(NULL));
	
	permutationTable = new int[256];
	gradientX = new float[256];
	gradientY = new float[256];
	gradientZ = new float[256];

	for (int i=0; i<256; ++i) {
		permutationTable[i] = i;

		gradientX[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
		gradientY[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
		gradientZ[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
	}

	int swapIndex = 0;
	int temp = 0;
	for (int i = 0; i < 256; i++) {
		swapIndex = rand() & 255;

		temp = permutationTable[i];
		permutationTable[i] = permutationTable[swapIndex];
		permutationTable[swapIndex] = temp;
	}
}

Perlin::~Perlin() {
	delete permutationTable;
	delete gradientX;
	delete gradientY;
	delete gradientZ;
}

float Perlin::lerp(float x) {
	return ((6.0f * x - 15.0f) * x + 10.0f) * pow(x, 3);
}

float Perlin::noise(float xCoord, float yCoord, float zCoord) {
	// Unit cube vertex coordinates surrounding the sample point
	int gradientX0 = int(floor(xCoord));
	int gradientX1 = gradientX0 + 1;
	int gradientY0 = int(floor(yCoord));
	int gradientY1 = gradientY0 + 1;
	int gradientZ0 = int(floor(zCoord));
	int gradientZ1 = gradientZ0 + 1;

	// Determine sample point position within unit cube
	float pointX0 = xCoord - float(gradientX0);
	float pointX1 = pointX0 - 1.0f;
	float pointY0 = yCoord - float(gradientY0);
	float pointY1 = pointY0 - 1.0f;
	float pointZ0 = zCoord - float(gradientZ0);
	float pointZ1 = pointZ0 - 1.0f;

	// Compute dot product between gradient and sample position vector
	int gradientIndex = permutationTable[(gradientX0 + permutationTable[(gradientY0 + permutationTable[gradientZ0 & 255]) & 255]) & 255];
	float dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;
	gradientIndex = permutationTable[(gradientX1 + permutationTable[(gradientY0 + permutationTable[gradientZ0 & 255]) & 255]) & 255];
	float dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;
	
	gradientIndex = permutationTable[(gradientX0 + permutationTable[(gradientY1 + permutationTable[gradientZ0 & 255]) & 255]) & 255];
	float dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;
	gradientIndex = permutationTable[(gradientX1 + permutationTable[(gradientY1 + permutationTable[gradientZ0 & 255]) & 255]) & 255];
	float dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;
	
	gradientIndex = permutationTable[(gradientX0 + permutationTable[(gradientY0 + permutationTable[gradientZ1 & 255]) & 255]) & 255];
	float dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;
	gradientIndex = permutationTable[(gradientX1 + permutationTable[(gradientY0 + permutationTable[gradientZ1 & 255]) & 255]) & 255];
	float dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

	gradientIndex = permutationTable[(gradientX0 + permutationTable[(gradientY1 + permutationTable[gradientZ1 & 255]) & 255]) & 255];
	float dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
	gradientIndex = permutationTable[(gradientX1 + permutationTable[(gradientY1 + permutationTable[gradientZ1 & 255]) & 255]) & 255];
	float dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
	
	float s = dotX0Y0Z0 + lerp(pointX0) * (dotX0Y0Z1 - dotX0Y0Z0);
	float t = dotX0Y1Z0 + lerp(pointX0) * (dotX0Y1Z1 - dotX0Y1Z0);
	float u = dotX1Y0Z0 + lerp(pointX0) * (dotX1Y0Z1 - dotX1Y0Z0);
	float v = dotX1Y1Z0 + lerp(pointX0) * (dotX1Y1Z1 - dotX1Y1Z0);
	float st = s + lerp(pointY0) * (t - s);
	float uv = u + lerp(pointY0) * (v - u);
	float result = st + lerp(pointZ0) * (uv - st);

	return result;
}

