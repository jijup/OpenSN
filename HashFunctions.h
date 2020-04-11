/*
 * HashFunctions.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementations for various pairing/hashing functions.
 */

#ifndef _HASHFUNCTIONS_H_
#define _HASHFUNCTIONS_H_

class HashFunctions {
public:
    HashFunctions();
    ~HashFunctions();

    //Returns the maximum integer of two given integers
    int max(int val1, int val2);
    
    // Linear Pairing Function
    int linearPair(int x, int y, int width);
    
    // Cantor Pairing Function
    int cantorPair(int x, int y);
    
    // Cantor Inversion Helper (Q value calculation)
    int cantorHelper(int z);
    
    // Cantor Inversion of X value
    int cantorInvertX(int z);
    
    // Cantor Inversion of Y value
    int cantorInvertY(int z);
    
    // Szudzik Pairing Function
    int szudzikPair(int x, int y);
    
    // Szudzik Inversion of X value
    int szudzikInvertX(int z);
    
    // Szudzik Inversion of Y value
    int szudzikInvertY(int z);
    
    // Rosenberg-Strong Pairing Function
    int rsPair(int x, int y);
    
    // Rosenberg-Strong Inversion M Calculation
    int rsInvert(int z);
};

#endif

