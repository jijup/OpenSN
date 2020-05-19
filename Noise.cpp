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
            noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72);

            /// Warping domain
            /*
            // Generate noise value - f((x, y, z) + f(x, y, z))
            float fp1 = noiseGenerator -> noise(noise + float(x) * invWidth, noise + float(y) * invHeight, noise + 0.72);

            // Generate noise value - f((x, y, z) + f((x, y, z) + f(x, y, z)))
            float fp2 = noiseGenerator -> noise(fp1 + float(x) * invWidth, fp1 + float(y) * invHeight, fp1 + 0.72);
            noise = fp2;
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

    printf("\nStarting curl noise generation.\n");

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

    printf("Successfully generated curl noise.\n");

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