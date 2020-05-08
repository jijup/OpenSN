/**
 * Driver.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Driver class for noise generation application, featuring various hashing/pairing functions.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "Renderer.h"

using namespace std;

/// Starting variables
// Noise Dimension Configuration
#define WIDTH 1000                  // X Resolution
#define HEIGHT 1000                 // Y Resolution

// Noise Type Configuration
//#define NOISE_TYPE 0                // Perlin noise
//#define NOISE_TYPE 1              // Gabor noise
//#define NOISE_TYPE 2              // Marble noise
#define NOISE_TYPE 3              // Worley noise
//#define NOISE_TYPE 4              // Curl noise
//#define NOISE_TYPE 5              // Bezier noise TODO: RENAME

// Pairing Function Configuration
//#define PAIRING_FUNCTION 0 	    // Linear
//#define PAIRING_FUNCTION 1 	        // Cantor
//#define PAIRING_FUNCTION 2 	    // Szudzik
#define PAIRING_FUNCTION 3        // Rosenberg-Strong

// Noise Image Save Configuration
//#define SAVE_NOISE_IMAGE 0        // Save noise image off
#define SAVE_NOISE_IMAGE 1		    // Save noise image on

// Application Configuration
#define APPLICATION_TYPE 0          // Apply texture to vase (or other object)
//#define APPLICATION_TYPE 1        // Procedural landscape model

// Analysis Mode Configuration
//#define ANALYSIS 0		        // Analysis mode off
#define ANALYSIS 1		            // Analysis mode on

// Amplitude Analysis Mode Configuration
//#define ANALYSIS_AMPLITUDE 0      // Amplitude analysis off
#define ANALYSIS_AMPLITUDE 1        // Amplitude analysis on

// Fourier Analysis Mode Configuration
//#define ANALYSIS_FOURIER 0        // Fourier analysis off
#define ANALYSIS_FOURIER 1          // Fourier analysis on


#undef main
int main() {

    printf("\nStarting application...\n\n");

    Renderer renderer = Renderer(WIDTH, HEIGHT, NOISE_TYPE, PAIRING_FUNCTION, SAVE_NOISE_IMAGE, APPLICATION_TYPE, ANALYSIS, ANALYSIS_AMPLITUDE, ANALYSIS_FOURIER);
    renderer.renderApplication();

    printf("\n\nApplication exited.\n");

    return 0;
}

