/**
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
    noiseGenerator->setPerlinDimensions(width, height);
    noiseGenerator->setPairingFunction(pairingFunction);
    noiseGenerator->setInitFrequency(4.0f);
    
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
            
            // Generate noise value - f(x, y, z)
            //noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72f);
            noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.5f);

            /// Warping domain
            /*
            // Generate noise value - f((x, y, z) + f(x, y, z))
            float fp1 = noiseGenerator -> noise(noise + float(x) * invWidth, noise + float(y) * invHeight, noise + 0.72);

            // Generate noise value - f((x, y, z) + f((x, y, z) + f(x, y, z)))
            float fp2 = noiseGenerator -> noise(fp1 + float(x) * invWidth, fp1 + float(y) * invHeight, fp1 + 0.72);
            float fp3 = noiseGenerator -> noise(fp2 + float(x) * invWidth, fp2 + float(y) * invHeight, fp2 + 0.72);
            float fp4 = noiseGenerator -> noise(fp3 + float(x) * invWidth, fp3 + float(y) * invHeight, fp3 + 0.72);
            noise = fp4;
             */

            // Set noise value dependant on hashed value
            int index = HashInstance.linearPair(x, y, width);
            noiseArray[index] = noise;

            // Keep track of minimum and maximum noise values
            if (noise < min) {
                min = noise;
            }

            if (noise > max) {
                max = noise;
            }
        }
    }

    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);

    printf("    Noise Values: Max: %f | Min: %f\n", max, min);
    
    // Invert Hash Functions
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


    printf("Successfully generated Perlin noise.\n");

    delete noiseGenerator;
    delete[] noiseArray;
    delete[] indexArray;
    return points;
}

/*
 * Generates gradient noise with Prime numbers replacing gradients.
 *
 * Parameters:
 *      pairingFunction: pairing function to be used
 *      noiseType: type of noise to be used
 *      width: number of x-axis pixels
 *      height: number of y-axis pixels
 *
 * Returns:
 *      vector: structs including Gradient noise values and coordinates.
 */
std::vector<Noise::Point> Noise::generatePrimedGradient(int pairingFunction, int noiseType, int width, int height) {

    printf("\nStarting primed gradient noise generation.\n");

    HashFunctions HashInstance;
    Fractal *noiseGenerator = new Fractal(noiseType);
    noiseGenerator->setPerlinDimensions(width, height);
    noiseGenerator->setPairingFunction(pairingFunction);
    noiseGenerator->setOctaves(8);
    noiseGenerator->setPGNOctaves(8);
    noiseGenerator->setInitFrequency(4.0f);

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

            // Generate noise value - f(x, y, z)
            noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 1.0f);
            //noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.5f);

            /// Warping domain
            /*
            // Generate noise value - f((x, y, z) + f(x, y, z))
            float fp1 = noiseGenerator -> noise(noise + float(x) * invWidth, noise + float(y) * invHeight, noise + 0.72);

            // Generate noise value - f((x, y, z) + f((x, y, z) + f(x, y, z)))
            float fp2 = noiseGenerator -> noise(fp1 + float(x) * invWidth, fp1 + float(y) * invHeight, fp1 + 0.72);
            float fp3 = noiseGenerator -> noise(fp2 + float(x) * invWidth, fp2 + float(y) * invHeight, fp2 + 0.72);
            float fp4 = noiseGenerator -> noise(fp3 + float(x) * invWidth, fp3 + float(y) * invHeight, fp3 + 0.72);
            noise = fp4;
             */

            // Set noise value dependant on hashed value
            int index = HashInstance.linearPair(x, y, width);
            noiseArray[index] = noise;

            // Keep track of minimum and maximum noise values
            if (noise < min) {
                min = noise;
            }

            if (noise > max) {
                max = noise;
            }
        }
    }

    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);

    printf("    Noise Values: Max: %f | Min: %f\n", max, min);

    // Invert Hash Functions
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


    printf("Successfully generated primed gradient noise.\n");

    delete noiseGenerator;
    delete[] noiseArray;
    delete[] indexArray;
    return points;
}

/*
 * Generates density/gradient noise with Prime numbers replacing gradients.
 *
 * Parameters:
 *      pairingFunction: pairing function to be used
 *      noiseType: type of noise to be used
 *      width: number of x-axis pixels
 *      height: number of y-axis pixels
 *
 * Returns:
 *      vector: structs containing noise values and coordinates.
 */
std::vector<Noise::Point> Noise::generatePrimedDensity(int pairingFunction, int noiseType, int width, int height) {

    printf("\nStarting primed gradient noise generation.\n");

    HashFunctions HashInstance;
    Fractal *noiseGenerator = new Fractal(noiseType);
    noiseGenerator->setPerlinDimensions(width, height);
    noiseGenerator->setPairingFunction(pairingFunction);
    noiseGenerator->setInitFrequency(4.0f);

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

            // Generate noise value - f(x, y, z)
            noise = noiseGenerator -> noise(float(x), float(y), 1.0f);
            //noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 1.0f);
            //noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.5f);

            /// Warping domain
            /*
            // Generate noise value - f((x, y, z) + f(x, y, z))
            float fp1 = noiseGenerator -> noise(noise + float(x) * invWidth, noise + float(y) * invHeight, noise + 0.72);

            // Generate noise value - f((x, y, z) + f((x, y, z) + f(x, y, z)))
            float fp2 = noiseGenerator -> noise(fp1 + float(x) * invWidth, fp1 + float(y) * invHeight, fp1 + 0.72);
            float fp3 = noiseGenerator -> noise(fp2 + float(x) * invWidth, fp2 + float(y) * invHeight, fp2 + 0.72);
            float fp4 = noiseGenerator -> noise(fp3 + float(x) * invWidth, fp3 + float(y) * invHeight, fp3 + 0.72);
            noise = fp4;
             */

            // Set noise value dependant on hashed value
            int index = HashInstance.linearPair(x, y, width);
            noiseArray[index] = noise;

            // Keep track of minimum and maximum noise values
            if (noise < min) {
                min = noise;
            }

            if (noise > max) {
                max = noise;
            }
        }
    }

    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);

    printf("    Noise Values: Max: %f | Min: %f\n", max, min);

    // Invert Hash Functions
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


    printf("Successfully generated primed gradient noise.\n");

    delete noiseGenerator;
    delete[] noiseArray;
    delete[] indexArray;
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

    HashFunctions HashInstance;
    Fractal *noiseGenerator = new Fractal(noiseType);
    noiseGenerator->setPerlinDimensions(width, height);
    noiseGenerator->setPairingFunction(pairingFunction);
    noiseGenerator->setInitFrequency(4.0f);

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
            int index = HashInstance.linearPair(x, y, width);
            noiseArray[index] = noise;

            // Keep track of minimum and maximum noise values
            if (noise < min) {
                min = noise;
            }

            if (noise > max) {
                max = noise;
            }
        }
    }

    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);

    printf("    Noise Values: Max: %f | Min: %f\n", max, min);

    // Invert Hash Functions
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

    printf("Successfully generated Gabor noise.\n");

    //std::vector<Noise::Point>().swap(points);

    delete noiseGenerator;
    delete[] noiseArray;
    delete[] indexArray;

    return points;
}

/*
 * Generates Perlin noise (with marble perturbation).
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

    printf("\nStarting Perlin noise (with marble perturbation) generation.\n");

    HashFunctions HashInstance;
    Fractal *noiseGenerator = new Fractal(noiseType);
    noiseGenerator->setPerlinDimensions(width, height);
    noiseGenerator->setPairingFunctionMarble(pairingFunction);
    noiseGenerator->setInitFrequency(4.0f);

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
            int index = HashInstance.linearPair(x, y, width);
            noiseArray[index] = noise;

            // Keep track of minimum and maximum noise values
            if (noise < min) {
                min = noise;
            }

            if (noise > max) {
                max = noise;
            }

        }
    }

    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);

    printf("    Noise Values: Max: %f | Min: %f\n", max, min);

    // Invert Hash Functions
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

    printf("Successfully generated Perlin noise (with marble perturbation).\n");

    //std::vector<Noise::Point>().swap(points);
    delete noiseGenerator;
    delete[] noiseArray;
    delete[] indexArray;
    return points;
}

/*
 * Generates Worley noise.
 *
 * Parameters:
 *      pairingFunction: pairing function to be used
 *      noiseType: type of noise to be used
 *      width: number of x-axis pixels
 *      height: number of y-axis pixels
 *
 * Returns:
 *      vector: structs including Worley noise values and coordinates.
 */
std::vector<Noise::Point> Noise::generateWorley(int pairingFunction, int noiseType, int width, int height) {

    printf("\nStarting Worley noise generation.\n");

    HashFunctions HashInstance;
    Fractal *noiseGenerator = new Fractal(noiseType);
    noiseGenerator->setPerlinDimensions(width, height);
    noiseGenerator->setPairingFunction(pairingFunction);
    noiseGenerator->setInitFrequency(4.0f);

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

    /// Progress variables
    int currLevel = 0;
    int percentFinished = 0;
    time_t startTime;
    time(&startTime);
    /// End progress variables

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            // Generate noise value
            noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72);

            /// Warp domain
            /**/
            // Generate noise value - f((x, y, z) + f(x, y, z))
            //float fp1 = noiseGenerator -> noise(noise + float(x) * invWidth, noise + float(y) * invHeight, noise + 0.72);
            //noise = fp1;

            // Generate noise value - f((x, y, z) + f((x, y, z) + f(x, y, z)))
            //float fp2 = noiseGenerator -> noise(fp1 + float(x) * invWidth, fp1 + float(y) * invHeight, fp1 + 0.72);
            //noise = fp2;

            // Generate noise value - f((x, y, z) + f((x, y, z) + f((x, y, z) + f(x, y, z))))
            //float fp3 = noiseGenerator -> noise(fp2 + float(x) * invWidth, fp2 + float(y) * invHeight, fp2 + 0.72);
            //noise = fp3;

            //noise = (noise + fp1) / 2.0f;
            //noise = (noise + fp1 + fp2) / 3.0f;
            //noise = (noise + fp1 + fp2 + fp3) / 4.0f;

            // Set noise value dependant on hashed value
            int index = HashInstance.linearPair(x, y, width);
            noiseArray[index] = noise;

            // Keep track of minimum and maximum noise values
            if (noise < min) {
                min = noise;
            }

            if (noise > max) {
                max = noise;
            }
        }

        /// ======= Display progress
        int progressFlag = 1;   //  0 - off  ||  1 - on
        if (progressFlag == 1) {
            if (x > currLevel) {

                int minutes, seconds;

                // Increment level and percent
                currLevel += 10;
                percentFinished += 1;

                // Get current time
                time_t currTime;
                time(&currTime);

                // Calculate total seconds to completion
                float timeDiff = difftime(currTime, startTime);
                float totalSeconds = timeDiff * (100.0f / ((float)percentFinished)) * (1.0f - ((float)percentFinished / 100.0f));
                int totalSecondsInt = (int) floor(totalSeconds);

                // Update minutes/seconds then print
                minutes = totalSecondsInt / 60;
                seconds = totalSecondsInt % 60;

                if (percentFinished > 5) {
                    printf("    Percent completed: %2d%% [Estimated time to completion: %d:%02d]\n", percentFinished - 5, minutes, seconds);
                } else {
                    printf("    Percent completed: --%% [Estimated time to completion: -:--]\n");
                }
            }
        }
        /// ======= End display progress
    }

    printf("    Noise Values: Max: %f | Min: %f\n", max, min);

    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);

    // Invert Hash Functions
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

    printf("Successfully generated Worley noise.\n");

    //std::vector<Noise::Point>().swap(points);
    delete noiseGenerator;
    delete[] noiseArray;
    delete[] indexArray;
    return points;
}

/*
 * Generates ExperimentalNoise noise.
 *
 * Parameters:
 *      pairingFunction: pairing function to be used
 *      noiseType: type of noise to be used
 *      width: number of x-axis pixels
 *      height: number of y-axis pixels
 *
 * Returns:
 *      vector: structs including ExperimentalNoise noise values and coordinates.
 */
std::vector<Noise::Point> Noise::generateExperiental(int pairingFunction, int noiseType, int width, int height) {

    printf("\nStarting experimental noise generation.\n");

    HashFunctions HashInstance;
    Fractal *noiseGenerator = new Fractal(noiseType);
    noiseGenerator->setPerlinDimensions(width, height);
    noiseGenerator->setPairingFunctionExperimental(pairingFunction);
    noiseGenerator->setInitFrequency(4.0f);

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

    /// Progress variables
    int currLevel = 0;
    int percentFinished = 0;
    time_t startTime;
    time(&startTime);
    /// End progress variables

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            // Generate noise value
            noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72);

            /// Warp domain
            /**/
            // Generate noise value - f((x, y, z) + f(x, y, z))
            //float fp1 = noiseGenerator -> noise(noise + float(x) * invWidth, noise + float(y) * invHeight, noise + 0.72);
            //noise = fp1;

            // Generate noise value - f((x, y, z) + f((x, y, z) + f(x, y, z)))
            //float fp2 = noiseGenerator -> noise(fp1 + float(x) * invWidth, fp1 + float(y) * invHeight, fp1 + 0.72);
            //noise = fp2;

            // Generate noise value - f((x, y, z) + f((x, y, z) + f((x, y, z) + f(x, y, z))))
            //float fp3 = noiseGenerator -> noise(fp2 + float(x) * invWidth, fp2 + float(y) * invHeight, fp2 + 0.72);
            //noise = fp3;

            //noise = (noise + fp1) / 2.0f;
            //noise = (noise + fp1 + fp2) / 3.0f;
            //noise = (noise + fp1 + fp2 + fp3) / 4.0f;

            // Set noise value dependant on hashed value
            int index = HashInstance.linearPair(x, y, width);
            noiseArray[index] = noise;

            // Keep track of minimum and maximum noise values
            if (noise < min) {
                min = noise;
            }

            if (noise > max) {
                max = noise;
            }
        }

        /// ======= Display progress
        int progressFlag = 1;   //  0 - off  ||  1 - on
        if (progressFlag == 1) {
            if (x > currLevel) {

                int minutes, seconds;

                // Increment level and percent
                currLevel += 10;
                percentFinished += 1;

                // Get current time
                time_t currTime;
                time(&currTime);

                // Calculate total seconds to completion
                float timeDiff = difftime(currTime, startTime);
                float totalSeconds = timeDiff * (100.0f / ((float)percentFinished)) * (1.0f - ((float)percentFinished / 100.0f));
                int totalSecondsInt = (int) floor(totalSeconds);

                // Update minutes/seconds then print
                minutes = totalSecondsInt / 60;
                seconds = totalSecondsInt % 60;

                if (percentFinished > 5) {
                    printf("    Percent completed: %2d%% [Estimated time to completion: %d:%02d]\n", percentFinished - 5, minutes, seconds);
                } else {
                    printf("    Percent completed: --%% [Estimated time to completion: -:--]\n");
                }
            }
        }
        /// ======= End display progress
    }

    // Debug
    printf("    Noise Values: Max: %f | Min: %f\n", max, min);

    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);

    // Invert Hash Functions
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            int index = HashInstance.linearPair(x, y, width);
            noise = noiseArray[index];

            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;

            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;

            //printf("before_noise: %f | after_noise: %f\n", temp, noise);

            points.push_back(Noise::Point());

            int i = x * height + y;
            points[i].x = x;
            points[i].y = y;
            points[i].colour = noise;

            //printf("X[%f] Y[%f] COLOUR[%f]\n", points[i].x, points[i].y, points[i].colour);
        }
    }

    printf("Successfully generated experimental noise.\n");

    //std::vector<Noise::Point>().swap(points);
    delete noiseGenerator;
    delete[] noiseArray;
    delete[] indexArray;
    return points;
}

/*
 * Generate Perlin noise (with splatter perturbation)
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
std::vector<Noise::Point> Noise::generateSplatter(int pairingFunction, int noiseType, int width, int height) {

    printf("\nStarting Perlin noise (with splatter perturbation) generation.\n");

    HashFunctions HashInstance;
    Fractal *noiseGenerator = new Fractal(noiseType);
    noiseGenerator->setPerlinDimensions(width, height);
    noiseGenerator->setPairingFunctionSplatter(pairingFunction);
    noiseGenerator->setInitFrequency(4.0f);

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
            int index = HashInstance.linearPair(x, y, width);
            noiseArray[index] = noise;

            // Keep track of minimum and maximum noise values
            if (noise < min) {
                min = noise;
            }

            if (noise > max) {
                max = noise;
            }

        }
    }

    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);

    printf("    Noise Values: Max: %f | Min: %f\n", max, min);

    // Invert Hash Functions
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

    printf("Successfully generated Perlin noise (with splatter perturbation).\n");

    //std::vector<Noise::Point>().swap(points);
    delete noiseGenerator;
    delete[] noiseArray;
    delete[] indexArray;
    return points;
}

/*
 * Generate Perlin noise (with wood perturbation)
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
std::vector<Noise::Point> Noise::generateWood(int pairingFunction, int noiseType, int width, int height) {

    printf("\nStarting Perlin noise (with wood perturbation) generation.\n");

    HashFunctions HashInstance;
    Fractal *noiseGenerator = new Fractal(noiseType);
    noiseGenerator->setPerlinDimensions(width, height);
    noiseGenerator->setPairingFunctionWood(pairingFunction);
    noiseGenerator->setInitFrequency(4.0f);

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
            int index = HashInstance.linearPair(x, y, width);
            noiseArray[index] = noise;

            // Keep track of minimum and maximum noise values
            if (noise < min) {
                min = noise;
            }

            if (noise > max) {
                max = noise;
            }

        }
    }

    // Convert noise values to pixel colour values.
    float temp = 1.0f / (max - min);

    printf("    Noise Values: Max: %f | Min: %f\n", max, min);

    // Invert Hash Functions
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

    printf("Successfully generated Perlin noise (with wood perturbation).\n");

    //std::vector<Noise::Point>().swap(points);
    delete noiseGenerator;
    delete[] noiseArray;
    delete[] indexArray;
    return points;
}