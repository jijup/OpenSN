/*
 * Analysis.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementations of various analysis techniques.
 */

#include "Noise.h"
#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <stb_image/stb_image_write.h>

#include <matplotlib-cpp/matplotlibcpp.h>
//#include <matplotlibcpp.h>
namespace plt = matplotlibcpp;

#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

class Analysis {
public:
    Analysis();
    ~Analysis();

    void runAnalysis(std::vector<Noise::Point> points, int pairingFunction, int noiseType, int width, int height, int ampAnalysis, int fourierAnalysis);
};

#endif