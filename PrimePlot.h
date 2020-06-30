/**
 * PrimePlot.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * An implementation of primes plotted as polar coordinates.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <opencv2/opencv.hpp>

#include <matplotlib-cpp/matplotlibcpp.h>
namespace plt = matplotlibcpp;

#ifndef _PRIMEPLOT_H_
#define _PRIMEPLOT_H_

class PrimePlot {
public:
    // Determines if a single value is prime
    bool isPrime(int val);

    void headerSVG(std::ofstream& outfile, int width, int height, std::string file);
    void footerSVG(std::ofstream& outfile);

    void generatePrimePlot();
    void generateUnitCircle();
    void generateGradientSVG();
    void generateGradientSVGCube();

    float fade(float x);
};

#endif