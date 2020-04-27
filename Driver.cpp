/**
 * Driver.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Driver for implementation of noise generation through various hashing/pairing functions.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "Noise.h"
#include "Point.h"
#include "Analysis.h"
#include "ImageSDL.h"
#include "Mesh.h"
#include "Texture.h"

using namespace std;

/// Constants
#define PI 3.14159265
#define WIDTH 1000       // X Resolution
#define HEIGHT 1000      // Y Resolution

/// Stringification helper
#define xstr(s) str(s)
#define str(s) #s

/// Analysis Mode Configuration
#define ANALYSIS 0		            // Analysis mode off
//#define ANALYSIS 1		        // Analysis mode on

/// TODO: ADD ANALYSIS_AMPLITUDE
//#define ANALYSIS_AMPLITUDE 0      // Amplitude analysis off
#define ANALYSIS_AMPLITUDE 1        // Amplitude analysis on

/// TODO: ADD ANALYSIS_FOURNIER
#define ANALYSIS_FOURNIER 0         // Fournier analysis off
//#define ANALYSIS_FOURNIER 1       // Fournier analysis on

/// Iterative Configurations
#define MULTIPLE_ITERATIONS 0       // Single iteration
//#define MULTIPLE_ITERATIONS 1     // Multiple iterations
#define NUMBER_OF_ITERATIONS 10     // Number of iterations if multiple is enabled

/// Noise Configuration
//#define NOISE_TYPE 0                // Perlin noise
//#define NOISE_TYPE 1              // Gabor noise
#define NOISE_TYPE 2              // Marble noise

/// BMP Noise Image Save Configuration
//#define SAVE_NOISE_IMAGE_BMP 0    // Save noise image as BMP off
#define SAVE_NOISE_IMAGE_BMP 1		// Save noise image as BMP on

/// Noise Image Rendering Configuration
#define RENDER_NOISE_IMAGE 0 	    // Render noise image off
//#define RENDER_NOISE_IMAGE 1	    // Render noise image on

/// Application Configuration
#define APPLICATION_TYPE 0          // Apply texture to vase (or other object)
//#define APPLICATION_TYPE 1        // Procedural landscape model

/// Pairing Function Configuration
//#define PAIRING_FUNCTION 0 	    // Linear
//#define PAIRING_FUNCTION 1 	        // Cantor
//#define PAIRING_FUNCTION 2 	    // Szudzik
#define PAIRING_FUNCTION 3        // Rosenberg-Strong

#if PAIRING_FUNCTION == 0
	#define TITLE 		            "Linear"
#elif PAIRING_FUNCTION == 1
	#define TITLE 		            "Cantor"
#elif PAIRING_FUNCTION == 2
	#define TITLE 		            "Szudzik"
#elif PAIRING_FUNCTION == 3
    #define TITLE                   "Rosenberg-Strong"
#else
	#define TITLE 		            "Other"
#endif


#undef main
int main() {

    Noise NoiseInstance;
    Analysis AnalysisInstance;
    ImageSDL imageInstance;
    Mesh meshInstance;
    Texture textureInstance;

    if (MULTIPLE_ITERATIONS == 0) {

        // Create title for image output
        string title = xstr(TITLE);
        if (NOISE_TYPE == 0) {
            title = "Perlin Noise - " + title;
        } else if (NOISE_TYPE == 1) {
            title = "Gabor Noise - " + title;
        } else if (NOISE_TYPE == 2) {
            title = "Perlin Noise (with Marble Perturbation) - " + title;
        } else {
            // TODO: Throw error
        }

        if (NOISE_TYPE == 0) {
            // Generate noise
            vector<Noise::Point> noise = NoiseInstance.generatePerlin(PAIRING_FUNCTION, NOISE_TYPE, WIDTH, HEIGHT);

            // Render and/or save noise
            imageInstance.renderImage(noise, SAVE_NOISE_IMAGE_BMP, RENDER_NOISE_IMAGE, WIDTH, HEIGHT, title);

            // Read in meshes from files
            std::vector<Mesh::s_Mesh> meshes = meshInstance.generateMesh();

            string pairingFunction = "";
            if (PAIRING_FUNCTION == 0) {
                pairingFunction = "Linear";
            } else if (PAIRING_FUNCTION == 1) {
                pairingFunction = "Cantor";
            } else if (PAIRING_FUNCTION == 2) {
                pairingFunction = "Szudzik";
            } else if (PAIRING_FUNCTION == 3) {
                pairingFunction = "RosenbergStrong";
            } else {
                // TODO: Throw error
            }

            string filename = "";
            if (APPLICATION_TYPE == 0) {
                filename += "Vase_Perlin_";
            } else if (APPLICATION_TYPE == 1) {
                filename += "ProceduralLandscape_Perlin_";
            } else {
                // TODO: Throw error
            }

            filename = filename + pairingFunction;

            // Generate textures from noise and render
            textureInstance.generateTexture(noise, meshes, filename);

            // Run Analysis if enabled (Amplitude & Fournier)
            if (ANALYSIS == 1) {
                AnalysisInstance.runAnalysis(noise, PAIRING_FUNCTION, NOISE_TYPE, WIDTH, HEIGHT, ANALYSIS_AMPLITUDE, ANALYSIS_FOURNIER);
            }
        } else if (NOISE_TYPE == 1) {
            vector<Noise::Point> noise = NoiseInstance.generateGabor(PAIRING_FUNCTION, NOISE_TYPE, WIDTH, HEIGHT);

            // Render and/or save noise
            imageInstance.renderImage(noise, SAVE_NOISE_IMAGE_BMP, RENDER_NOISE_IMAGE, WIDTH, HEIGHT, title);

            // Read in meshes from files
            std::vector<Mesh::s_Mesh> meshes = meshInstance.generateMesh();

            string pairingFunction = "";
            if (PAIRING_FUNCTION == 0) {
                pairingFunction = "Linear";
            } else if (PAIRING_FUNCTION == 1) {
                pairingFunction = "Cantor";
            } else if (PAIRING_FUNCTION == 2) {
                pairingFunction = "Szudzik";
            } else if (PAIRING_FUNCTION == 3) {
                pairingFunction = "RosenbergStrong";
            } else {
                // TODO: Throw error
            }

            string filename = "";
            if (APPLICATION_TYPE == 0) {
                filename += "Vase_Gabor_";
            } else if (APPLICATION_TYPE == 1) {
                filename += "ProceduralLandscape_Gabor_";
            } else {
                // TODO: Throw error
            }

            filename = filename + pairingFunction;

            // Generate textures from noise and render
            textureInstance.generateTexture(noise, meshes, filename);

            // Run Analysis if enabled (Amplitude & Fournier)
            if (ANALYSIS == 1) {
                AnalysisInstance.runAnalysis(noise, PAIRING_FUNCTION, NOISE_TYPE, WIDTH, HEIGHT, ANALYSIS_AMPLITUDE, ANALYSIS_FOURNIER);
            }
        } else if (NOISE_TYPE == 2) {
            // Generate Noise
            vector<Noise::Point> noise = NoiseInstance.generateMarble(PAIRING_FUNCTION, NOISE_TYPE, WIDTH, HEIGHT);

            // Render and/or save noise
            imageInstance.renderImage(noise, SAVE_NOISE_IMAGE_BMP, RENDER_NOISE_IMAGE, WIDTH, HEIGHT, title);

            // Read in meshes from files
            std::vector<Mesh::s_Mesh> meshes = meshInstance.generateMesh();

            string pairingFunction = "";
            if (PAIRING_FUNCTION == 0) {
                pairingFunction = "Linear";
            } else if (PAIRING_FUNCTION == 1) {
                pairingFunction = "Cantor";
            } else if (PAIRING_FUNCTION == 2) {
                pairingFunction = "Szudzik";
            } else if (PAIRING_FUNCTION == 3) {
                pairingFunction = "RosenbergStrong";
            } else {
                // TODO: Throw error
            }

            string filename = "";
            if (APPLICATION_TYPE == 0) {
                filename += "Vase_Marble_";
            } else if (APPLICATION_TYPE == 1) {
                filename += "ProceduralLandscape_Marble_";
            } else {
                // TODO: Throw error
            }

            filename = filename + pairingFunction;

            // Generate textures from noise and render
            textureInstance.generateTexture(noise, meshes, filename);

            // Run Analysis if enabled (Amplitude & Fournier)
            if (ANALYSIS == 1) {
                AnalysisInstance.runAnalysis(noise, PAIRING_FUNCTION, NOISE_TYPE, WIDTH, HEIGHT, ANALYSIS_AMPLITUDE, ANALYSIS_FOURNIER);
            }
        } else {
            // TODO: Handle error
        }
    } else if (MULTIPLE_ITERATIONS == 1) {

        // Create title for image output
        string title = xstr(TITLE);
        if (NOISE_TYPE == 0) {
            title = "Perlin Noise - " + title;

        } else if (NOISE_TYPE == 1) {
            title = "Gabor Noise - " + title;
        } else {
            // TODO: Throw error
        }

        for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
            if (NOISE_TYPE == 0) {
                vector<Noise::Point> noise = NoiseInstance.generatePerlin(PAIRING_FUNCTION, NOISE_TYPE, WIDTH, HEIGHT);
                imageInstance.renderImage(noise, SAVE_NOISE_IMAGE_BMP, 0, WIDTH, HEIGHT, title);

                if (ANALYSIS == 1) {
                    AnalysisInstance.runAnalysis(noise, PAIRING_FUNCTION, NOISE_TYPE, WIDTH, HEIGHT, ANALYSIS_AMPLITUDE, ANALYSIS_FOURNIER);
                }
            } else if (NOISE_TYPE == 1) {
                vector<Noise::Point> noise = NoiseInstance.generatePerlin(PAIRING_FUNCTION, NOISE_TYPE, WIDTH, HEIGHT);
                imageInstance.renderImage(noise, SAVE_NOISE_IMAGE_BMP, 0, WIDTH, HEIGHT, title);

                if (ANALYSIS == 1) {
                    AnalysisInstance.runAnalysis(noise, PAIRING_FUNCTION, NOISE_TYPE, WIDTH, HEIGHT, ANALYSIS_AMPLITUDE, ANALYSIS_FOURNIER);
                }
            } else {
                // TODO: Handle error
            }
        }
    } else {
        // TODO: Handle error
    }

    return 0;
}

