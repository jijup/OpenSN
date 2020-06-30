/**
 * PrimeGradient.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A gradient noise implementation with prime numbers as gradients.
 */

#include "PrimeGradient.h"

PrimeGradient::PrimeGradient() {
    this->currentOctave = 0;
}

PrimeGradient::~PrimeGradient() {
    delete[] prime;
}

bool PrimeGradient::isPrime(int val) {

    for (int i = 2; i*i <= val; i++) {
        if (val % i == 0) {
            return false;
        }
    }

    return true;
}

void PrimeGradient::sieve(int offset, int numPrimes) {

    int current = 2;
    int count = 0;
    int countOffset = 0;

    // Output numPrimes
    printf("    numPrimes: %d\n", numPrimes);

    // Loop until numPrimes is reached
    //std::cout << "    primes [";
    while (count < numPrimes) {

        if (current == 2 || current == 3 || isPrime(current)) {
            if (++countOffset > offset) {
                this->prime[count] = current;
                //std::cout << this->prime[count] << ", ";

                if (++count > numPrimes) {
                    break;
                }
            }
        }
        current++;
    }

    //std::cout << "]" << std::endl;
}

void PrimeGradient::setDimensions(int width, int height) {
    this->width = width;
    this->height = height;
}

void PrimeGradient::setPairingFunction(int pairingFunction) {
    this->pairingFunction = pairingFunction;
}

void PrimeGradient::setNumOctaves(int numOctaves) {
    this->numOctaves = numOctaves;

    generatePrimeTable();
}

void PrimeGradient::updateCurrentOctave(int currentOctave) {
    this->currentOctave = currentOctave;
    //this->currentOctave = 3;
}

void PrimeGradient::generatePermutationTables() {

    int dimensionFlag = 0;
    if (dimensionFlag == 0) {

        // Permute permP
        std::cout << "    primeP: [";
        for (int i = this->numPrimes - 1; i > 0; i--) {
            int swapIndex = rand() % (i + 1);

            int temp = this->prime[i];
            this->prime[i] = this->prime[swapIndex];
            this->prime[swapIndex] = temp;

            std::cout << this->prime[i] << ", ";
        }
        std::cout << "]" << std::endl;

    } else {
        this->permP = new int[this->numPrimes];
        this->permQ = new int[this->numPrimes];

        // Fill tables with values prime numbers
        for (int i = 0; i < this->numPrimes; i++) {
            this->permP[i] = this->prime[i];
            this->permQ[i] = this->prime[i];
        }

        // Permute permP
        std::cout << "    primeP: [";
        for (int i = this->numPrimes - 1; i > 0; i--) {
            int swapIndex = rand() % (i + 1);

            int temp = this->permP[i];
            this->permP[i] = this->permP[swapIndex];
            this->permP[swapIndex] = temp;

            std::cout << this->permP[i] << ", ";
        }
        std::cout << "]" << std::endl;

        // Permute permQ
        std::cout << "    primeQ: [";
        for (int i = this->numPrimes - 1; i > 0; i--) {
            int swapIndex = rand() % (i + 1);

            int temp = this->permQ[i];
            this->permQ[i] = this->permQ[swapIndex];
            this->permQ[swapIndex] = temp;

            std::cout << this->permQ[i] << ", ";
        }
        std::cout << "]\n" << std::endl;
    }


}

void PrimeGradient::generatePrimeTable() {
    srand(time(NULL));

    // Setup primes generation factors
    int initialNumPrimes = 256;
    this->numPrimes = initialNumPrimes + pow(2, this->numOctaves - 1) - 1;

    this->offset = 0;
    this->prime = new int[this->numPrimes];

    // Sieve for primes
    sieve(this->offset, this->numPrimes);

    // Generate permutation tables
    srand(time(NULL));
    generatePermutationTables();
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

    // Higher order smoothing [5]
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

    int prime, p, q, index;
    float dotX0Y0Z0, dotX0Y0Z1, dotX0Y1Z0, dotX0Y1Z1, dotX1Y0Z0, dotX1Y0Z1, dotX1Y1Z0, dotX1Y1Z1;
    float _u;

    // Generate vectors
    int dimensionFlag = 1;          // 0 - 3D | 1 - 2D
    if (dimensionFlag == 0) {
        //this->currentOctave = 0;

        index = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY0) & 255, gradientZ0) & 255 + (int)(pow(2, this->currentOctave)) - 1;
        p = this->prime[this->permP[index]];
        q = this->prime[this->permQ[index]];
        _u = ((q - floor(q / (2.0f * M_PI)) * (2.0f * M_PI)) / M_PI) - 1.0f;
        dotX0Y0Z0 = pointX0 * (sqrt(1 - pow(_u, 2.0f)) * cos(p)) + pointY0 * (sqrt(1 - pow(_u, 2.0f)) * sin(p)) + pointZ0 * _u;

        index = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY0) & 255, gradientZ0) & 255 + (int)(pow(2, this->currentOctave)) - 1;
        p = this->prime[this->permP[index]];
        q = this->prime[this->permQ[index]];
        _u = ((q - floor(q / (2.0f * M_PI)) * (2.0f * M_PI)) / M_PI) - 1.0f;
        dotX1Y0Z0 = pointX1 * (sqrt(1 - pow(_u, 2.0f)) * cos(p)) + pointY0 * (sqrt(1 - pow(_u, 2.0f)) * sin(p)) + pointZ0 * _u;

        index = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY1) & 255, gradientZ0) & 255 + (int)(pow(2, this->currentOctave)) - 1;
        p = this->prime[this->permP[index]];
        q = this->prime[this->permQ[index]];
        _u = ((q - floor(q / (2.0f * M_PI)) * (2.0f * M_PI)) / M_PI) - 1.0f;
        dotX0Y1Z0 = pointX0 * (sqrt(1 - pow(_u, 2.0f)) * cos(p)) + pointY1 * (sqrt(1 - pow(_u, 2.0f)) * sin(p)) + pointZ0 * _u;

        index = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY1) & 255, gradientZ0) & 255 + (int)(pow(2, this->currentOctave)) - 1;
        p = this->prime[this->permP[index]];
        q = this->prime[this->permQ[index]];
        _u = ((q - floor(q / (2.0f * M_PI)) * (2.0f * M_PI)) / M_PI) - 1.0f;
        dotX1Y1Z0 = pointX1 * (sqrt(1 - pow(_u, 2.0f)) * cos(p)) + pointY1 * (sqrt(1 - pow(_u, 2.0f)) * sin(p)) + pointZ0 * _u;

        index = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY0) & 255, gradientZ1) & 255 + (int)(pow(2, this->currentOctave)) - 1;
        p = this->prime[this->permP[index]];
        q = this->prime[this->permQ[index]];
        _u = ((q - floor(q / (2.0f * M_PI)) * (2.0f * M_PI)) / M_PI) - 1.0f;
        dotX0Y0Z1 = pointX0 * (sqrt(1 - pow(_u, 2.0f)) * cos(p)) + pointY0 * (sqrt(1 - pow(_u, 2.0f)) * sin(p)) + pointZ1 * _u;

        index = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY0) & 255, gradientZ1) & 255 + (int)(pow(2, this->currentOctave)) - 1;
        p = this->prime[this->permP[index]];
        q = this->prime[this->permQ[index]];
        _u = ((q - floor(q / (2.0f * M_PI)) * (2.0f * M_PI)) / M_PI) - 1.0f;
        dotX1Y0Z1 = pointX1 * (sqrt(1 - pow(_u, 2.0f)) * cos(p)) + pointY0 * (sqrt(1 - pow(_u, 2.0f)) * sin(p)) + pointZ1 * _u;

        index = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX0, gradientY1) & 255, gradientZ1) & 255 + (int)(pow(2, this->currentOctave)) - 1;
        p = this->prime[this->permP[index]];
        q = this->prime[this->permQ[index]];
        _u = ((q - floor(q / (2.0f * M_PI)) * (2.0f * M_PI)) / M_PI) - 1.0f;
        dotX0Y1Z1 = pointX0 * (sqrt(1 - pow(_u, 2.0f)) * cos(p)) + pointY1 * (sqrt(1 - pow(_u, 2.0f)) * sin(p)) + pointZ1 * _u;

        index = this->hashInstance.szudzikPair(this->hashInstance.szudzikPair(gradientX1, gradientY1) & 255, gradientZ1) & 255 + (int)(pow(2, this->currentOctave)) - 1;
        p = this->prime[this->permP[index]];
        q = this->prime[this->permQ[index]];
        _u = ((q - floor(q / (2.0f * M_PI)) * (2.0f * M_PI)) / M_PI) - 1.0f;
        dotX1Y1Z1 = pointX1 * (sqrt(1 - pow(_u, 2.0f)) * cos(p)) + pointY1 * (sqrt(1 - pow(_u, 2.0f)) * sin(p)) + pointZ1 * _u;

        float s = lerp(dotX0Y0Z1, dotX1Y0Z1, pointX0);
        float t = lerp(dotX0Y1Z1, dotX1Y1Z1, pointX0);
        float u = lerp(dotX0Y0Z0, dotX1Y0Z0, pointX0);
        float v = lerp(dotX0Y1Z0, dotX1Y1Z0, pointX0);

        float st = lerp(s, t, pointY0);
        float uv = lerp(u, v, pointY0);

        float result = lerp(st, uv, pointZ0);
        return result;                                  // 1 (fractal normal)
        //return abs(result);                           // 2 (fractal ridged)
        //return 1.0f / abs(result);                    // 3 (fractal cellular)
    } else if (dimensionFlag == 1) {

        //this->currentOctave = 0;

        //prime = this->prime[(this->hashInstance.szudzikPair(gradientX0, gradientY0) & 255)];
        prime = this->prime[(this->hashInstance.szudzikPair(gradientX0, gradientY0) & 255)] + (int)(pow(2, this->currentOctave)) - 1;
        dotX0Y0Z0 = pointX0 * cos(prime) + pointY0 * sin(prime);

        //prime = this->prime[(this->hashInstance.szudzikPair(gradientX1, gradientY0) & 255)];
        prime = this->prime[(this->hashInstance.szudzikPair(gradientX1, gradientY0) & 255)] + (int)(pow(2, this->currentOctave)) - 1;
        dotX1Y0Z0 = pointX1 * cos(prime) + pointY0 * sin(prime);

        //prime = this->prime[(this->hashInstance.szudzikPair(gradientX0, gradientY1) & 255)];
        prime = this->prime[(this->hashInstance.szudzikPair(gradientX0, gradientY1) & 255)] + (int)(pow(2, this->currentOctave)) - 1;
        dotX0Y1Z0 = pointX0 * cos(prime) + pointY1 * sin(prime);

        //prime = this->prime[(this->hashInstance.szudzikPair(gradientX1, gradientY1) & 255)];
        prime = this->prime[(this->hashInstance.szudzikPair(gradientX1, gradientY1) & 255)] + (int)(pow(2, this->currentOctave)) - 1;
        dotX1Y1Z0 = pointX1 * cos(prime) + pointY1 * sin(prime);

        float st = lerp(dotX0Y0Z0, dotX1Y0Z0, pointX0);
        float uv = lerp(dotX0Y1Z0, dotX1Y1Z0, pointX0);
        float result = lerp(st, uv, pointY0);

        // Traditional
        return result;

        // Hybrid fBm
        //return (result + 0.6f) / 1.25f;
        //return (result + 1.0f) / 2.0f;

        // Ridges
        //return (1.0f - abs(result)) * 2.0f - 1.0f;      // Ridges
        //return pow((1.0f - abs(result)) * 2.0f - 1.0f, 2);      // Ridges (adjusted for normalized distribution)

        // Wood
        /*glm::vec2 position = glm::vec2(xCoord, yCoord) * 0.1f;
        position += glm::vec2(10.0f, 10.0f);
        float noise = (float) sqrt((position.x * position.x) + (position.y * position.y));
        return glm::fract(result * noise);*/

    } else {
        // TODO: Throw error
        return 0;
    }
}
