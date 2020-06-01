/**
 * PrimeGradient.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A gradient noise implementation with prime numbers as gradients.
 */

#include "PrimeGradient.h"

PrimeGradient::PrimeGradient() {
    srand(time(NULL));

    // Randomize prime table
    int swapIndex = 0;
    int temp = 0;
    for (int i = 0; i < 256; i++) {
        swapIndex = rand() & 255;

        temp = prime[i];
        prime[i] = prime[swapIndex];
        prime[swapIndex] = temp;
    }
}

PrimeGradient::~PrimeGradient() {}

void PrimeGradient::setDimensions(int width, int height) {
    this->width = width;
    this->height = height;
}

void PrimeGradient::setPairingFunction(int pairingFunction) {
    this->pairingFunction = pairingFunction;
}

float PrimeGradient::fade(float x) {

    /**
     * In ascending order of slope at (0.5, 0.5). See image in analysis folder.
     * [1] and [2] very alike. [3] and [4] very alike.
     */

    // Cubic (original gradient noise) [1]
    //return x * x * (3.0f - 2.0f * x);

    // Cos ease [2]
    //return pow(cos(3.14159f * (x - 1.0f) / 2.0f), 2.0f);

    // Quintic (better gradient noise) [3]
    return ((6.0f * x - 15.0f) * x + 10.0f) * x * x * x;

    // Parametric [4]
    //return pow(x, 2.0f) / (pow(x, 2.0f) + pow(1.0f - x, 2.0f));

    // Higher order smoothing (via Kyle McDonald) [5]
    //return -20.0f * pow(x, 7) + 70.0f * pow(x, 6) - 84.0f * pow(x, 5) + 35.0f * pow(x, 4);

    // Averaged smoothing [6] (([3] + [5]) / 2)
    //return x * x * x * (-10.0f * x * x * x * x + 35.0f * x * x * x - 39.0f * x * x + 10.0f * x + 5.0f);
}

float PrimeGradient::lerp(float a, float b, float x) {
    return a + fade(x) * (b - a);
}

float PrimeGradient::noise(float xCoord, float yCoord, float zCoord) {

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

    int gradientIndex, prime;
    float dotX0Y0Z0, dotX0Y0Z1, dotX0Y1Z0, dotX0Y1Z1, dotX1Y0Z0, dotX1Y0Z1, dotX1Y1Z0, dotX1Y1Z1;

    // Generate vectors
    prime = this->prime[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY0) & 255, gradientZ0) & 255];
    //dotX0Y0Z0 = pointX0 * cos(prime) + pointY0 * sin(prime);                                                          // 2D
    dotX0Y0Z0 = pointX0 * sin(prime) * cos(prime) + pointY0 * sin(prime) * sin(prime) + pointZ0 * cos(prime);           // 3D

    prime = this->prime[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY0) & 255, gradientZ0) & 255];
    //dotX1Y0Z0 = pointX1 * cos(prime) + pointY0 * sin(prime);                                                          // 2D
    dotX1Y0Z0 = pointX1 * sin(prime) * cos(prime) + pointY0 * sin(prime) * sin(prime) + pointZ0 * cos(prime);           // 3D

    prime = this->prime[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY1) & 255, gradientZ0) & 255];
    //dotX0Y1Z0 = pointX0 * cos(prime) + pointY1 * sin(prime);                                                          // 2D
    dotX0Y1Z0 = pointX0 * sin(prime) * cos(prime) + pointY1 * sin(prime) * sin(prime) + pointZ0 * cos(prime);           // 3D

    prime = this->prime[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY1) & 255, gradientZ0) & 255];
    //dotX1Y1Z0 = pointX1 * cos(prime) + pointY1 * sin(prime);                                                          // 2D
    dotX1Y1Z0 = pointX1 * sin(prime) * cos(prime) + pointY1 * sin(prime) * sin(prime) + pointZ0 * cos(prime);           // 3D

    prime = this->prime[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY0) & 255, gradientZ1) & 255];
    //dotX0Y0Z1 = pointX0 * cos(prime) + pointY0 * sin(prime);                                                          // 2D
    dotX0Y0Z1 = pointX0 * sin(prime) * cos(prime) + pointY0 * sin(prime) * sin(prime) + pointZ1 * cos(prime);           // 3D

    prime = this->prime[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY0) & 255, gradientZ1) & 255];
    //dotX1Y0Z1 = pointX1 * cos(prime) + pointY0 * sin(prime);                                                          // 2D
    dotX1Y0Z1 = pointX1 * sin(prime) * cos(prime) + pointY0 * sin(prime) * sin(prime) + pointZ1 * cos(prime);           // 3D

    prime = this->prime[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY1) & 255, gradientZ1) & 255];
    //dotX0Y1Z1 = pointX0 * cos(prime) + pointY1 * sin(prime);                                                          // 2D
    dotX0Y1Z1 = pointX0 * sin(prime) * cos(prime) + pointY1 * sin(prime) * sin(prime) + pointZ1 * cos(prime);           // 3D

    prime = this->prime[this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY1) & 255, gradientZ1) & 255];
    //dotX1Y1Z1 = pointX1 * cos(prime) + pointY1 * sin(prime);                                                          // 2D
    dotX1Y1Z1 = pointX1 * sin(prime) * cos(prime) + pointY1 * sin(prime) * sin(prime) + pointZ1 * cos(prime);           // 3D

    float s = lerp(dotX0Y0Z1, dotX1Y0Z1, pointX0);
    float t = lerp(dotX0Y1Z1, dotX1Y1Z1, pointX0);
    float u = lerp(dotX0Y0Z0, dotX1Y0Z0, pointX0);
    float v = lerp(dotX0Y1Z0, dotX1Y1Z0, pointX0);

    float st = lerp(s, t, pointY0);
    float uv = lerp(u, v, pointY0);

    float result = lerp(st, uv, pointZ0);
    return result;                                // 1 (fractal normal)
    //return abs(result);                           // 2 (fractal ridged)
    //return 1.0f / abs(result);                    // 3 (fractal cellular?)

}
