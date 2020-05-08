/**
 * Curl.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of Curl noise.
 */


#ifndef _CURL_H_
#define _CURL_H_

class Curl {
public:
    Curl();
    ~Curl();



    // Generates a Curl noise value between, given some 3D coordinates (X, Y, Z).
    float noise(float sample_x, float sample_y, float sample_z);

private:



};

#endif






