/**
 * Perlin.cpp
 *
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 */

#include "Perlin.h"

Perlin::Perlin() {
	srand(time(NULL));

	permutationTable = new int[256];
	gradientX = new float[256];
	gradientY = new float[256];
	gradientZ = new float[256];

	int permutationUsage = 1; // 0 - Random permutation | 1 - Perlin's permutation
	if (permutationUsage == 0) {
        for (int i = 0; i < 256; ++i) {
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
	} else {
        for (int i = 0; i < 256; ++i) {
            permutationTable[i] = permutation[i];
            //permutationTable[i] = i;

            gradientX[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
            gradientY[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
            gradientZ[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
        }
	}
}

Perlin::~Perlin() {
	delete permutationTable;
	delete gradientX;
	delete gradientY;
	delete gradientZ;
}

void Perlin::setDimensions(int width, int height) {
    this->width = width;
    this->height = height;
}

void Perlin::setPairingFunction(int pairingFunction) {
    this->pairingFunction = pairingFunction;
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

    int gradientIndex;
    float dotX0Y0Z0, dotX0Y0Z1, dotX0Y1Z0, dotX0Y1Z1, dotX1Y0Z0, dotX1Y0Z1, dotX1Y1Z0, dotX1Y1Z1;

    if (this->pairingFunction == 0) {                  /// Linear Hashing
        // Compute dot product between gradient and sample position vector
        gradientIndex = permutationTable[this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX0, gradientY0, this->width) & 255, gradientZ0, this->width) & 255];
        dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX1, gradientY0, this->width) & 255, gradientZ0, this->width) & 255];
        dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX0, gradientY1, this->width) & 255, gradientZ0, this->width) & 255];
        dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX1, gradientY1, this->width) & 255, gradientZ0, this->width) & 255];
        dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX0, gradientY0, this->width) & 255, gradientZ1, this->width) & 255];
        dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX1, gradientY0, this->width) & 255, gradientZ1, this->width) & 255];
        dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX0, gradientY1, this->width) & 255, gradientZ1, this->width) & 255];
        dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX1, gradientY1, this->width) & 255, gradientZ1, this->width) & 255];
        dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
    } else if (this->pairingFunction == 1) {        /// Cantor Hashing
        // Compute dot product between gradient and sample position vector
        gradientIndex = permutationTable[this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX0, gradientY0) & 255, gradientZ0) & 255];
        dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX1, gradientY0) & 255, gradientZ0) & 255];
        dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX0, gradientY1) & 255, gradientZ0) & 255];
        dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX1, gradientY1) & 255, gradientZ0) & 255];
        dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX0, gradientY0) & 255, gradientZ1) & 255];
        dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX1, gradientY0) & 255, gradientZ1) & 255];
        dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX0, gradientY1) & 255, gradientZ1) & 255];
        dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX1, gradientY1) & 255, gradientZ1) & 255];
        dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
    } else if (this->pairingFunction == 2) {        /// Szudzik Hashing
        // Compute dot product between gradient and sample position vector
        gradientIndex = permutationTable[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY0) & 255, gradientZ0) & 255];
        dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY0) & 255, gradientZ0) & 255];
        dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY1) & 255, gradientZ0) & 255];
        dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY1) & 255, gradientZ0) & 255];
        dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY0) & 255, gradientZ1) & 255];
        dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY0) & 255, gradientZ1) & 255];
        dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY1) & 255, gradientZ1) & 255];
        dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY1) & 255, gradientZ1) & 255];
        dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
    } else if (this->pairingFunction == 3) {        /// Rosenberg-Strong Hashing
        // Compute dot product between gradient and sample position vector
        gradientIndex = permutationTable[this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX0, gradientY0) & 255, gradientZ0) & 255];
        dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX1, gradientY0) & 255, gradientZ0) & 255];
        dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX0, gradientY1) & 255, gradientZ0) & 255];
        dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX1, gradientY1) & 255, gradientZ0) & 255];
        dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX0, gradientY0) & 255, gradientZ1) & 255];
        dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX1, gradientY0) & 255, gradientZ1) & 255];
        dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX0, gradientY1) & 255, gradientZ1) & 255];
        dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX1, gradientY1) & 255, gradientZ1) & 255];
        dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
    } else if (this->pairingFunction == 4) {        /// Original Perlin Hashing
        // Compute dot product between gradient and sample position vector
        gradientIndex = permutationTable[(gradientX0 + permutationTable[(gradientY0 + permutationTable[gradientZ0 & 255]) & 255]) & 255];
        dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[(gradientX1 + permutationTable[(gradientY0 + permutationTable[gradientZ0 & 255]) & 255]) & 255];
        dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[(gradientX0 + permutationTable[(gradientY1 + permutationTable[gradientZ0 & 255]) & 255]) & 255];
        dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[(gradientX1 + permutationTable[(gradientY1 + permutationTable[gradientZ0 & 255]) & 255]) & 255];
        dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = permutationTable[(gradientX0 + permutationTable[(gradientY0 + permutationTable[gradientZ1 & 255]) & 255]) & 255];
        dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[(gradientX1 + permutationTable[(gradientY0 + permutationTable[gradientZ1 & 255]) & 255]) & 255];
        dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[(gradientX0 + permutationTable[(gradientY1 + permutationTable[gradientZ1 & 255]) & 255]) & 255];
        dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = permutationTable[(gradientX1 + permutationTable[(gradientY1 + permutationTable[gradientZ1 & 255]) & 255]) & 255];
        dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
    } else {
        // TODO: Throw error
    }

    /*
    /// Without permutation table
    if (this->pairingFunction == 0) {                  /// Linear Hashing
        // Compute dot product between gradient and sample position vector
        gradientIndex = this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX0, gradientY0, this->width) & 255, gradientZ0, this->width) & 255;
        dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX1, gradientY0, this->width) & 255, gradientZ0, this->width) & 255;
        dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX0, gradientY1, this->width) & 255, gradientZ0, this->width) & 255;
        dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX1, gradientY1, this->width) & 255, gradientZ0, this->width) & 255;
        dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX0, gradientY0, this->width) & 255, gradientZ1, this->width) & 255;
        dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX1, gradientY0, this->width) & 255, gradientZ1, this->width) & 255;
        dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX0, gradientY1, this->width) & 255, gradientZ1, this->width) & 255;
        dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.linearPair(this->hashInstance.linearPair(gradientX1, gradientY1, this->width) & 255, gradientZ1, this->width) & 255;
        dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
    } else if (this->pairingFunction == 1) {        /// Cantor Hashing
        // Compute dot product between gradient and sample position vector
        gradientIndex = this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX0, gradientY0) & 255, gradientZ0) & 255;
        dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX1, gradientY0) & 255, gradientZ0) & 255;
        dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX0, gradientY1) & 255, gradientZ0) & 255;
        dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX1, gradientY1) & 255, gradientZ0) & 255;
        dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX0, gradientY0) & 255, gradientZ1) & 255;
        dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX1, gradientY0) & 255, gradientZ1) & 255;
        dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX0, gradientY1) & 255, gradientZ1) & 255;
        dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.cantorPair(this->hashInstance.cantorPair(gradientX1, gradientY1) & 255, gradientZ1) & 255;
        dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
    } else if (this->pairingFunction == 2) {        /// Szudzik Hashing
        // Compute dot product between gradient and sample position vector
        gradientIndex = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY0) & 255, gradientZ0) & 255;
        dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY0) & 255, gradientZ0) & 255;
        dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY1) & 255, gradientZ0) & 255;
        dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY1) & 255, gradientZ0) & 255;
        dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY0) & 255, gradientZ1) & 255;
        dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY0) & 255, gradientZ1) & 255;
        dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY1) & 255, gradientZ1) & 255;
        dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY1) & 255, gradientZ1) & 255;
        dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
    } else if (this->pairingFunction == 3) {        /// Rosenberg-Strong Hashing
        // Compute dot product between gradient and sample position vector
        gradientIndex = this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX0, gradientY0) & 255, gradientZ0) & 255;
        dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX1, gradientY0) & 255, gradientZ0) & 255;
        dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX0, gradientY1) & 255, gradientZ0) & 255;
        dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX1, gradientY1) & 255, gradientZ0) & 255;
        dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX0, gradientY0) & 255, gradientZ1) & 255;
        dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX1, gradientY0) & 255, gradientZ1) & 255;
        dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX0, gradientY1) & 255, gradientZ1) & 255;
        dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = this->hashInstance.rsPair(this->hashInstance.rsPair(gradientX1, gradientY1) & 255, gradientZ1) & 255;
        dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
    } else if (this->pairingFunction == 4) {        /// Original Perlin Hashing
        // Compute dot product between gradient and sample position vector
        gradientIndex = (gradientX0 + (gradientY0 + gradientZ0 & 255) & 255) & 255;
        dotX0Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = (gradientX1 + (gradientY0 + gradientZ0 & 255) & 255) & 255;
        dotX0Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = (gradientX0 + (gradientY1 + gradientZ0 & 255) & 255) & 255;
        dotX0Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = (gradientX1 + (gradientY1 + gradientZ0 & 255) & 255) & 255;
        dotX0Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ0;

        gradientIndex = (gradientX0 + (gradientY0 + gradientZ1 & 255) & 255) & 255;
        dotX1Y0Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = (gradientX1 + (gradientY0 + gradientZ1 & 255) & 255) & 255;
        dotX1Y0Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY0 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = (gradientX0 + (gradientY1 + gradientZ1 & 255) & 255) & 255;
        dotX1Y1Z0 = gradientX[gradientIndex] * pointX0 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;

        gradientIndex = (gradientX1 + (gradientY1 + gradientZ1 & 255) & 255) & 255;
        dotX1Y1Z1 = gradientX[gradientIndex] * pointX1 + gradientY[gradientIndex] * pointY1 + gradientZ[gradientIndex] * pointZ1;
    } else {
        // TODO: Throw error
    }
     */

	// Interpolate
	float s = dotX0Y0Z0 + lerp(pointX0) * (dotX0Y0Z1 - dotX0Y0Z0);
	float t = dotX0Y1Z0 + lerp(pointX0) * (dotX0Y1Z1 - dotX0Y1Z0);
	float u = dotX1Y0Z0 + lerp(pointX0) * (dotX1Y0Z1 - dotX1Y0Z0);
	float v = dotX1Y1Z0 + lerp(pointX0) * (dotX1Y1Z1 - dotX1Y1Z0);
	float st = s + lerp(pointY0) * (t - s);
	float uv = u + lerp(pointY0) * (v - u);

	// Perlin Noise
	float result = st + lerp(pointZ0) * (uv - st);
	return result;

	// Perlin Noise with Ridges
	//return (1.0f - abs(result)) * 2.0f - 1.0f;

    // Random Noise
	//return (float(rand()) / (RAND_MAX/2)) - 1.0f;
}
