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

    // Generates permutation table via Yates shuffle
    void generatePermutationTables();

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

	int primeTest[263] = {1433, 1553, 571, 149, 937, 1399, 439, 337, 229, 1367, 89, 821, 1097, 401, 109, 1483, 5, 359, 743, 1231, 281, 1439, 1277, 1637, 1291, 683, 1297, 491, 617, 761, 59, 953, 127, 587, 1301, 223, 103, 1499, 2, 929, 797, 719, 919, 137, 1409, 1039, 101, 131, 839, 283, 1237, 557, 787, 827, 983, 1153, 433, 1229, 1289, 1307, 293, 479, 1459, 1489, 1373, 1103, 13, 1049, 419, 1031, 631, 941, 691, 599, 607, 1223, 199, 1163, 1249, 547, 1187, 233, 1217, 331, 1091, 251, 97, 1451, 1487, 947, 1279, 773, 1429, 997, 1259, 197, 1061, 647, 1471, 653, 991, 523, 751, 739, 863, 733, 307, 1117, 643, 271, 1523, 1601, 977, 1657, 1427, 1667, 809, 43, 1531, 757, 1093, 31, 1607, 1033, 463, 1663, 23, 467, 367, 181, 443, 1669, 661, 179, 1181, 1493, 509, 677, 139, 191, 163, 317, 641, 1613, 79, 1627, 29, 883, 1381, 1319, 1021, 7, 3, 1567, 461, 1571, 37, 709, 71, 1013, 569, 1109, 257, 1621, 313, 227, 881, 379, 1151, 73, 593, 151, 1321, 971, 1009, 373, 11, 449, 1327, 157, 907, 1579, 521, 211, 311, 173, 701, 853, 53, 1201, 1087, 19, 1619, 1019, 239, 1447, 563, 17, 47, 353, 241, 541, 277, 823, 727, 829, 1543, 1453, 107, 487, 859, 503, 193, 41, 1069, 577, 1193, 1283, 887, 269, 409, 113, 499, 431, 811, 349, 61, 673, 1609, 347, 1583, 877, 1423, 769, 1303, 911, 1129, 613, 967, 1123, 1171, 1549, 67, 263, 601, 421, 167, 619, 1213, 389, 659, 1597, 1511, 397, 1481, 1559, 457, 857, 1361, 1051, 383, 83};

private:
	int width;
	int height;

	HashFunctions hashInstance;
	int pairingFunction;

    int numPrimes, offset;
	int *prime;

	int numOctaves;
	int currentOctave;

	int *permutationTable;
	int *permP;
    int *permQ;
};

#endif
