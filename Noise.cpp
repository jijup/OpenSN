/*
 * Noise.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Driver function for noise generation.
 */

#include "Noise.h"

Noise::Noise() {}

Noise::~Noise() {}

/*
 * Generates Perlin noise.
 *
 * Parameters:
 *      pairingFunction: pairing function to be used
 *      noiseType: type of noise to be used
 *      width: number of x-axis pixels
 *      height: number of y-axis pixels
 *
 * Returns:
 *      vector: structs including Perlin noise values and coordinates.
 */
std::vector<Noise::Point> Noise::generatePerlin(int pairingFunction, int noiseType, int width, int height) {

    printf("\nStarting Perlin noise generation.\n");

    HashFunctions HashInstance;
    Fractal *noiseGenerator = new Fractal(noiseType);
    noiseGenerator -> setInitFrequency(4.0f);
    
    // Define array size
    unsigned long long int arr_size = pow(width, 2) * pow(height, 2);
    int *indexArray = new int[width * height];
    int indexArrayCurr = 0;
    
    // Intialize nosie array
    float *noiseArray = new float[arr_size];
    
    // Generate a noise value for each pixel
    float invWidth = 1.0f / float(width);
    float invHeight = 1.0f / float(height);
    float noise;
    float min = 0.0f;
    float max = 0.0f;
    
    std::vector<Noise::Point> points;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            
            // Generate noise value
            noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72);
            
            // Set noise value dependant on hashed value
            if (pairingFunction == 0) {
                int index = HashInstance.linearPair(x, y, width);
                noiseArray[index] = noise;

                // Keep track of minimum and maximum noise values
                if (noise < min) {
                    min = noise;
                }

                if (noise > max) {
                    max = noise;
                }
            } else if (pairingFunction == 1) {
                int index = HashInstance.cantorPair(x, y);
                indexArray[indexArrayCurr++] = index;

                noiseArray[index] = noise;

                // Keep track of minimum and maximum noise values
                if (noise < min) {
                    min = noise;
                }

                if (noise > max) {
                    max = noise;
                }
            } else if (pairingFunction == 2) {
                int index = HashInstance.szudzikPair(x, y);
                indexArray[indexArrayCurr++] = index;

                noiseArray[index] = noise;

                // Keep track of minimum and maximum noise values
                if (noise < min) {
                    min = noise;
                }

                if (noise > max) {
                    max = noise;
                }
            } else if (pairingFunction == 3) {
                int index = HashInstance.rsPair(x, y);
                indexArray[indexArrayCurr++] = index;

                noiseArray[index] = noise;

                // Keep track of minimum and maximum noise values
                if (noise < min) {
                    min = noise;
                }

                if (noise > max) {
                    max = noise;
                }
            } else {
                // TODO: Throw error
            }

        }
    }
    
    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);
    
    // Invert Hash Functions
    if (pairingFunction == 0) {

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {

                int index = HashInstance.linearPair(x, y, width);
                noise = noiseArray[index];

                // Use gaussian distribution of noise values to fill [-1, 1] range.
                noise = -1.0f + 2.0f * (noise - min) * temp;

                // Remap to RGB friendly colour values in range [0, 1].
                noise += 1.0f;
                noise *= 0.5f;

                points.push_back(Noise::Point());

                int i = x * height + y;
                points[i].x = x;
                points[i].y = y;
                points[i].colour = noise;

                //printf("X[%f] Y[%f] COLOUR[%f]\n", points[i].x, points[i].y, points[i].colour);
            }
        }
    } else if (pairingFunction == 1) {
        
        for (int i = 0; i < (height * width); i++) {
            
            int index = indexArray[i];
            int inv_x = HashInstance.cantorInvertX(index);
            int inv_y = HashInstance.cantorInvertY(index);
            
            noise = noiseArray[index];
            
            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;
            
            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;
            
            points.push_back(Noise::Point());
            points[i].x = inv_x;
            points[i].y = inv_y;
            points[i].colour = noise;
        }
    } else if (pairingFunction == 2) {

        for (int i = 0; i < (height * width); i++) {

            int index = indexArray[i];
            int inv_x = HashInstance.szudzikInvertX(index);
            int inv_y = HashInstance.szudzikInvertY(index);

            noise = noiseArray[index];

            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;

            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;

            points.push_back(Noise::Point());
            points[i].x = inv_x;
            points[i].y = inv_y;
            points[i].colour = noise;
        }
    } else if (pairingFunction == 3) {
        for (int i = 0; i < (height * width); i++) {
            int m = HashInstance.rsInvert(i);
            
            int inv_x = 0;
            int inv_y = 0;
            int tempVar = i - pow(m, 2);
            if ((i - pow(m, 2)) < m) {
                inv_x = i - pow(m, 2);
                inv_y = m;
            } else {
                inv_x = m;
                inv_y = pow(m, 2) + (2*m) - i;
            }
            
            noise = noiseArray[i];

            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;

            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;
            
            points.push_back(Noise::Point());
            points[i].x = inv_x;
            points[i].y = inv_y;
            points[i].colour = noise;
        }
    } else {
        // TODO: Throw error
    }

    printf("Successfully generated Perlin noise.\n");
    return points;
}

/*
 * Generates Gabor noise.
 *
 * Parameters:
 *      pairingFunction: pairing function to be used
 *      noiseType: type of noise to be used
 *      width: number of x-axis pixels
 *      height: number of y-axis pixels
 *
 * Returns:
 *      vector: structs including Gabor noise values and coordinates.
 */
std::vector<Noise::Point> Noise::generateGabor(int pairingFunction, int noiseType, int width, int height) {

    printf("\nStarting Gabor noise generation.\n");

    // TODO: Implement Gabor noise
    std::vector<Noise::Point> points;

    printf("\nSuccessfully generated Gabor noise.\n");
    return points;
}

/*
 * Generates Marble noise.
 *
 * Parameters:
 *      pairingFunction: pairing function to be used
 *      noiseType: type of noise to be used
 *      width: number of x-axis pixels
 *      height: number of y-axis pixels
 *
 * Returns:
 *      vector: structs including Perlin noise values and coordinates.
 */
std::vector<Noise::Point> Noise::generateMarble(int pairingFunction, int noiseType, int width, int height) {

    printf("\nStarting marble noise generation.\n");

    HashFunctions HashInstance;
    Fractal *noiseGenerator = new Fractal(noiseType);
    noiseGenerator -> setInitFrequency(4.0f);

    // Define array size
    unsigned long long int arr_size = pow(width, 2) * pow(height, 2);
    int *indexArray = new int[width * height];
    int indexArrayCurr = 0;

    // Intialize nosie array
    float *noiseArray = new float[arr_size];

    // Generate a noise value for each pixel
    float invWidth = 1.0f / float(width);
    float invHeight = 1.0f / float(height);
    float noise;
    float min = 0.0f;
    float max = 0.0f;

    std::vector<Noise::Point> points;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            // Generate noise value
            noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72);

            // Set noise value dependant on hashed value
            if (pairingFunction == 0) {
                int index = HashInstance.linearPair(x, y, width);
                noiseArray[index] = noise;

                // Keep track of minimum and maximum noise values
                if (noise < min) {
                    min = noise;
                }

                if (noise > max) {
                    max = noise;
                }
            } else if (pairingFunction == 1) {
                int index = HashInstance.cantorPair(x, y);
                indexArray[indexArrayCurr++] = index;

                noiseArray[index] = noise;

                // Keep track of minimum and maximum noise values
                if (noise < min) {
                    min = noise;
                }

                if (noise > max) {
                    max = noise;
                }
            } else if (pairingFunction == 2) {
                int index = HashInstance.szudzikPair(x, y);
                indexArray[indexArrayCurr++] = index;

                noiseArray[index] = noise;

                // Keep track of minimum and maximum noise values
                if (noise < min) {
                    min = noise;
                }

                if (noise > max) {
                    max = noise;
                }
            } else if (pairingFunction == 3) {
                int index = HashInstance.rsPair(x, y);
                indexArray[indexArrayCurr++] = index;

                noiseArray[index] = noise;

                // Keep track of minimum and maximum noise values
                if (noise < min) {
                    min = noise;
                }

                if (noise > max) {
                    max = noise;
                }
            } else {
                // TODO: Throw error
            }

        }
    }

    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);

    // Invert Hash Functions
    if (pairingFunction == 0) {

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {

                int index = HashInstance.linearPair(x, y, width);
                noise = noiseArray[index];

                // Use gaussian distribution of noise values to fill [-1, 1] range.
                noise = -1.0f + 2.0f * (noise - min) * temp;

                // Remap to RGB friendly colour values in range [0, 1].
                noise += 1.0f;
                noise *= 0.5f;

                points.push_back(Noise::Point());

                int i = x * height + y;
                points[i].x = x;
                points[i].y = y;
                points[i].colour = noise;

                //printf("X[%f] Y[%f] COLOUR[%f]\n", points[i].x, points[i].y, points[i].colour);
            }
        }
    } else if (pairingFunction == 1) {

        for (int i = 0; i < (height * width); i++) {

            int index = indexArray[i];
            int inv_x = HashInstance.cantorInvertX(index);
            int inv_y = HashInstance.cantorInvertY(index);

            noise = noiseArray[index];

            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;

            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;

            points.push_back(Noise::Point());
            points[i].x = inv_x;
            points[i].y = inv_y;
            points[i].colour = noise;

            //printf("X[%f] Y[%f] COLOUR[%f]\n", points[i].x, points[i].y, points[i].colour);
        }
    } else if (pairingFunction == 2) {

        for (int i = 0; i < (height * width); i++) {

            int index = indexArray[i];
            int inv_x = HashInstance.szudzikInvertX(index);
            int inv_y = HashInstance.szudzikInvertY(index);

            noise = noiseArray[index];

            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;

            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;

            points.push_back(Noise::Point());
            points[i].x = inv_x;
            points[i].y = inv_y;
            points[i].colour = noise;

            //printf("X[%f] Y[%f] COLOUR[%f]\n", points[i].x, points[i].y, points[i].colour);
        }
    } else if (pairingFunction == 3) {
        for (int i = 0; i < (height * width); i++) {
            int m = HashInstance.rsInvert(i);

            int inv_x = 0;
            int inv_y = 0;
            int tempVar = i - pow(m, 2);
            if ((i - pow(m, 2)) < m) {
                inv_x = i - pow(m, 2);
                inv_y = m;
            } else {
                inv_x = m;
                inv_y = pow(m, 2) + (2*m) - i;
            }

            noise = noiseArray[i];

            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;

            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;

            points.push_back(Noise::Point());
            points[i].x = inv_x;
            points[i].y = inv_y;
            points[i].colour = noise;

            //printf("X[%d] Y[%d] COLOUR[%f]\n", points[i].x, points[i].y, points[i].colour);
        }
    } else {
        // TODO: Throw error
    }

    printf("Successfully generated marble noise.\n");
    return points;
}



