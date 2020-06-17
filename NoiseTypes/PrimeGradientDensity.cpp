/**
 * PrimeGradientDensity.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A gradient noise implementation with prime number density as gradients.
 */

#include "PrimeGradientDensity.h"

PrimeGradientDensity::PrimeGradientDensity() {
    srand(time(NULL));

    // Set offsets
    this->offsetX = 0;
    this->offsetY = 0;
}

PrimeGradientDensity::~PrimeGradientDensity() {}

bool PrimeGradientDensity::isPrime(int val) {

    for (int i = 2; i*i <= val; i++) {
        if (val % i == 0) {
            return false;
        }
    }

    return true;
}

void PrimeGradientDensity::setDimensions(int width, int height) {
    this->width = width;
    this->height = height;
}

void PrimeGradientDensity::setPairingFunction(int pairingFunction) {
    this->pairingFunction = pairingFunction;
}

float PrimeGradientDensity::fade(float x) {

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

float PrimeGradientDensity::lerp(float a, float b, float x) {
    return a + fade(x) * (b - a);
}

float PrimeGradientDensity::noise(float xCoord, float yCoord, float zCoord) {

    /// ===== 2 Dimensional
    int width = 1000;
    int height = 1000;

    float avg;

    if ((int)xCoord > 0 && (int)xCoord < (width - 1) && (int)yCoord > 0 && (int)yCoord < (height - 1)) {            // Inner

        int x1y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord)) ? 1 : 0;
        int x2y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord)) ? 1 : 0;
        int x0y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord)) ? 1 : 0;
        int x1y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord + 1)) ? 1 : 0;
        int x2y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord + 1)) ? 1 : 0;
        int x0y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord + 1)) ? 1 : 0;
        int x1y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord - 1)) ? 1 : 0;
        int x2y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord - 1)) ? 1 : 0;
        int x0y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord - 1)) ? 1 : 0;

        avg = (x1y1 + x2y1 + x0y1 + x1y2 + x2y2 + x0y2 + x1y0 + x2y0 + x0y0) / 9.0f;

    } else if ((int)xCoord == 0 && (int)yCoord > 0 && (int)yCoord < (height - 1)) {                            // Edge (left)

        int x1y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord)) ? 1 : 0;
        int x2y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord)) ? 1 : 0;
        int x1y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord + 1)) ? 1 : 0;
        int x2y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord + 1)) ? 1 : 0;
        int x1y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord - 1)) ? 1 : 0;
        int x2y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord - 1)) ? 1 : 0;

        avg = (x1y1 + x2y1 + x1y2 + x2y2 + x1y0 + x2y0) / 6.0f;

    } else if ((int)xCoord == (width - 1) && (int)yCoord > 0 && (int)yCoord < (height - 1)) {                  // Edge (right)

        int x1y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord)) ? 1 : 0;
        int x0y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord)) ? 1 : 0;
        int x1y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord + 1)) ? 1 : 0;
        int x0y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord + 1)) ? 1 : 0;
        int x1y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord - 1)) ? 1 : 0;
        int x0y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord - 1)) ? 1 : 0;

        avg = (x1y1 + x0y1 + x1y2 + x0y2 + x1y0 + x0y0) / 6.0f;

    } else if ((int)yCoord == 0 && (int)xCoord > 0 && (int)xCoord < (width - 1)) {                             // Edge (top)

        int x1y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord)) ? 1 : 0;
        int x2y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord)) ? 1 : 0;
        int x0y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord)) ? 1 : 0;
        int x1y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord - 1)) ? 1 : 0;
        int x2y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord - 1)) ? 1 : 0;
        int x0y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord - 1)) ? 1 : 0;

        avg = (x1y1 + x2y1 + x0y1 + x1y0 + x2y0 + x0y0) / 6.0f;

    } else if ((int)yCoord == (height - 1) && (int)xCoord > 0 && (int)xCoord < (width - 1)) {                  // Edge (bottom)

        int x1y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord)) ? 1 : 0;
        int x2y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord)) ? 1 : 0;
        int x0y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord)) ? 1 : 0;
        int x1y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord + 1)) ? 1 : 0;
        int x2y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord + 1)) ? 1 : 0;
        int x0y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord + 1)) ? 1 : 0;

        avg = (x1y1 + x2y1 + x0y1 + x1y2 + x2y2 + x0y2) / 6.0f;

    } else if ((int)xCoord == 0 && (int)yCoord == 0) {                                                    // Corner (top left)

        int x1y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord)) ? 1 : 0;
        int x2y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord)) ? 1 : 0;
        int x1y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord - 1)) ? 1 : 0;
        int x2y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord - 1)) ? 1 : 0;

        //printf("\ntop-left [(%d, %d) - %f]\n%d %d \n%d %d\n\nn", (int)xCoord, (int)yCoord, avg, x1y1, x2y1, x1y0, x2y0);

        avg = (x1y1 + x2y1 + x1y0 + x2y0) / 4.0f;

    } else if ((int)xCoord == (width - 1) && (int)yCoord == 0) {                                          // Corner (top right)

        int x1y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord)) ? 1 : 0;
        int x0y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord)) ? 1 : 0;
        int x1y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord - 1)) ? 1 : 0;
        int x0y0 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord - 1)) ? 1 : 0;

        avg = (x1y1 + x0y1 + x1y0 + x0y0) / 4.0f;

    } else if ((int)xCoord == 0 && (int)yCoord == (height - 1)) {                                         // Corner (bottom left)

        int x1y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord)) ? 1 : 0;
        int x2y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord)) ? 1 : 0;
        int x1y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord + 1)) ? 1 : 0;
        int x2y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord + 1, (int)yCoord + 1)) ? 1 : 0;

        avg = (x1y1 + x2y1 + x1y2 + x2y2) / 4.0f;

    } else if ((int)xCoord == (width - 1) && (int)yCoord == (height - 1)) {                               // Corner (bottom right)

        int x1y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord)) ? 1 : 0;
        int x0y1 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord)) ? 1 : 0;
        int x1y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord, (int)yCoord + 1)) ? 1 : 0;
        int x0y2 = isPrime(this->hashInstance.szudzikPair((int)xCoord - 1, (int)yCoord + 1)) ? 1 : 0;

        avg = (x1y1 + x0y1 + x1y2 + x0y2) / 4.0f;

    }

    return (sqrt(0.25f + avg) - 0.5f) * 2.0f + (1.0f / 6.0f);
}
