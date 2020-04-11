/*
 * Analysis.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementations for various analysis techniques.
 */

#include "Noise.h"
#include <iostream>
#include <fstream>
#include <string>

#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

class Analysis {
public:
    Analysis();
    ~Analysis();

    void runAnalysis(std::vector<Noise::Point> points, int pairingFunction, int noiseType, int textureType, int width, int height, int ampAnalysis, int fournierAnalysis);


};

#endif