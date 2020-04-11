/*
 * HashFunctions.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementations for various pairing/hashing functions.
 */

#include "HashFunctions.h"
#include <math.h>

HashFunctions::HashFunctions() {}

HashFunctions::~HashFunctions() {}

/**
 * Returns the maximum integer of two given integers.
 */
int HashFunctions::max(int val1, int val2) {
    return (val1 > val2) ? val1 : val2;
}

/*
 * Linear pairing function.
 *
 * Parameters:
 *      x: x coordinate
 *      y: y coordinate
 *      width: pixels in x-dimension
 *
 * Returns:
 *      int: paired value
 */
int HashFunctions::linearPair(int x, int y, int width) {
    return (y * width + x);
}

/*
 * Cantor pairing function.
 *
 * Parameters:
 *      x: x coordinate
 *      y: y coordinate
 *
 * Returns:
 *      int: paired value
 */
int HashFunctions::cantorPair(int x, int y) {
    return (((x + y) * (x + y + 1)) / 2 + y);
}

/*
 * Helper function for Cantor inversion. Finds Q value.
 *
 * Parameters:
 *      z: Hashed value
 *
 * Returns:
 *      int: Q value
 */
int HashFunctions::cantorHelper(int z) {
    return (floor((-1 + sqrt(1 + 8 * z)) / 2));
}

/*
 * Inversion of Cantor pairing function (X value).
 *
 * Parameters:
 *      z: Hashed value
 *
 * Returns:
 *      int: Inverted x value
 */
int HashFunctions::cantorInvertX(int z) {
    int q = cantorHelper(z);
    return ((q * (3 + q)) / 2 - z);
}

/*
 * Inversion of Cantor pairing function (Y value).
 *
 * Parameters:
 *      z: Hashed value
 *
 * Returns:
 *      int: Inverted y value
 */
int HashFunctions::cantorInvertY(int z) {
    int q = cantorHelper(z);
    return (z - (q * (1 + q)) / 2);
}

/*
 * Szudzik pairing function.
 *
 * Parameters:
 *      x: x coordinate
 *      y: y coordinate
 *
 * Returns:
 *      int: paired value
 */
int HashFunctions::szudzikPair(int x, int y) {
    return ((x >= y) ? (pow(x, 2) + x + y) : (pow(y, 2) + x));
}

/*
 * Inversion of Szudzik pairing function (X value).
 *
 * Parameters:
 *      z: Hashed value
 *
 * Returns:
 *      int: Inverted x value
 */
int HashFunctions::szudzikInvertX(int z) {
    int temp = floor(sqrt(z));
    if (z - pow(temp, 2) < temp) {
        return (z - pow(temp, 2));
    } else {
        return temp;
    }
}

/*
 * Inversion of Szudzik pairing function (Y value).
 *
 * Parameters:
 *      z: Hashed value
 *
 * Returns:
 *      int: Inverted y value
 */
int HashFunctions::szudzikInvertY(int z) {
    int temp = floor(sqrt(z));
    if (z - pow(temp, 2) < temp) {
        return temp;
    } else {
        return (z - pow(temp, 2) - temp);
    }
}

/*
 * Rosenberg-Strong function.
 *
 * Parameters:
 *      x: x coordinate
 *      y: y coordinate
 *
 * Returns:
 *      int: paired value
 */
int HashFunctions::rsPair(int x, int y) {
    int tempMax = max(x, y);
    return pow(tempMax, 2) + tempMax + x - y;
}

/*
 * Helper function for Rosenberg-Strong inversion. Finds M value.
 *
 * Parameters:
 *      z: Hashed value
 *
 * Returns:
 *      int: M value
 */
int HashFunctions::rsInvert(int z) {
    return floor(sqrt(z));
}
