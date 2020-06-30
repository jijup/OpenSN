/**
 * Analysis.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementations of various analysis techniques. Usage of OpenCV documentation for Fourier analysis. See reference.
 *
 * Reference: (https://docs.opencv.org/3.4/d8/d01/tutorial_discrete_fourier_transform.html).
 */

#include "Noise.h"
#include "HashFunctions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <stb_image/stb_image_write.h>

#include <matplotlib-cpp/matplotlibcpp.h>
namespace plt = matplotlibcpp;

#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

class Analysis {
public:
    Analysis();
    ~Analysis();

    void runAnalysis(std::vector<Noise::Point> points, int pairingFunction, int noiseType, int width, int height, int ampAnalysis, int fourierAnalysis);
    void runAnalysis(std::vector<Noise::Point3D> points, int pairingFunction, int noiseType, int width, int height, int ampAnalysis, int fourierAnalysis);
};

#endif