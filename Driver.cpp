/* 
 * Driver.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Driver for the implementation of Perlin noise via various hashing/pairing functions.
 */

#include <SDL.h>	// CMake
//#include <SDL2/SDL.h>	// Makefile
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "Fractal.h"


using namespace std;

/**
 * Constants
 */
#define PI 3.14159265
#define WIDTH 1000       // X Resolution
#define HEIGHT 1000      // Y Resolution

/**
 * Mode Configuration
 */
#define TESTING 0		// Testing mode off
//#define TESTING 1		// Testing mode on

//#define ANALYSIS 0		// Analysis mode off
#define ANALYSIS 1		// Analysis mode on

#define FOURNIER 0      // Fournier analysis off
//#define FOURNIER 1      // Fournier analysis on

#define ANALYSIS_TYPE 0     	// Multiple iterations of same parameters
//#define ANALYSIS_TYPE 1   	// Multiple iterations of varying parameters

//#define IMAGE_OUTPUT 0 	// Image output off
#define IMAGE_OUTPUT 1		// Image output on

//#define PAIRING_FUNCTION 0 	// Linear
//#define PAIRING_FUNCTION 1 	// Cantor
//#define PAIRING_FUNCTION 2 	// Szudzik
#define PAIRING_FUNCTION 3 // Rosenberg-Strong


// Linear Pairing Function
int linearPair(int x, int y) {
	return (y * WIDTH + x);
}

// Cantor Pairing Function
int cantorPair(int x, int y) {
	return (((x + y) * (x + y + 1)) / 2 + y);
}

// Cantor Inversion Helper (Q value calculation)
int cantorHelper(int z) {
	return (floor((-1 + sqrt(1 + 8 * z)) / 2));
}

// Cantor Inversion of X value
int cantorInvertX(int z) {
	int q = cantorHelper(z);
	return ((q * (3 + q)) / 2 - z);
}

// Cantor Inversion of Y value
int cantorInvertY(int z) {
	int q = cantorHelper(z);
	return (z - (q * (1 + q)) / 2);
}

// Szudzik Pairing Function
int szudzikPair(int x, int y) {
	return ((x >= y) ? (pow(x, 2) + x + y) : (pow(y, 2) + x));	
}

// Szudzik Inversion of X value
int szudzikInvertX(int z) {
	int temp = floor(sqrt(z));
	if (z - pow(temp, 2) < temp) {
		return (z - pow(temp, 2));
	} else {
		return temp;
	}
}

// Szudzik Inversion of Y value
int szudzikInvertY(int z) {
	int temp = floor(sqrt(z));
	if (z - pow(temp, 2) < temp) {
		return temp;
	} else {
		return (z - pow(temp, 2) - temp);
	}
}

// Rosenberg-Strong Pairing Function
int rsPair(int x, int y) {
    int tempMax = max(x, y);
    return pow(tempMax, 2) + tempMax + x - y;
}

// Rosenberg-Strong Inversion M Calculation
int rsInvert(int z) {
    return floor(sqrt(z));
}

// Colours pixel at given position, (x, y). Assumes 32 bits per pixel.
void colourPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
	Uint32 *p = (Uint32 *)surface -> pixels + y * surface -> w + x;
	*p = pixel;
}

#if PAIRING_FUNCTION == 0	    // Linear
	#define TITLE 		    "Perlin Noise - Linear"
	#define HASH(x, y)  	linearPair(x, y)
	#define INVERT_X(z)	1
	#define INVERT_Y(z)	1
#elif PAIRING_FUNCTION == 1	// Cantor
	#define TITLE 		    "Perlin Noise - Cantor"
	#define HASH(x, y)  	cantorPair(x, y)
	#define INVERT_X(z)	cantorInvertX(z)
	#define INVERT_Y(z)	cantorInvertY(z)
#elif PAIRING_FUNCTION == 2	// Szudzik
	#define TITLE 		    "Perlin Noise - Szudzik"
	#define HASH(x, y)  	szudzikPair(x, y)
	#define INVERT_X(z)	szudzikInvertX(z)
	#define INVERT_Y(z)	szudzikInvertY(z)
#elif PAIRING_FUNCTION == 3  // Rosenberg-Strong
    #define TITLE         "Perlin Noise - Rosenberg-Strong"
    #define HASH(x, y)    rsPair(x, y)
    #define INVERT_X(z)   1
    #define INVERT_Y(z)   1
#else				          // Other
	#define TITLE 		"Perlin Noise - Other"
	#define HASH(x, y)  	(y * WIDTH + x)
#endif

struct point {
    int x;
    int y;
    float colour;
};

/**
 * Returns the maximum integer of two given integers.
 */
int max(int val1, int val2) {
    return (val1 > val2) ? val1 : val2;
}

/**
 *
 *
 */
int generateImage() {
    // Initialize noise
    Fractal *noiseGenerator = new Fractal();
    noiseGenerator -> setInitFrequency(4.0f);
    
    // Define array size
    unsigned long long int arr_size = pow(WIDTH, 2) * pow(HEIGHT, 2);
    int *indexArray = new int[WIDTH * HEIGHT];
    int indexArrayCurr = 0;
    
    // Intialize nosie array
    float *noiseArray = new float[arr_size];
    
    // Initialize Amplitude Distribution Array
    float *ampDistributionArray = new float[WIDTH * HEIGHT];
    
    
    // Initialize SDL window, renderer, image and texture
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *image = NULL;
    SDL_Texture *imageTexture = NULL;
    
    // SDL Window Creation
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Error during SDL initialization." << endl;
        return 0;
    }
    
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (!window) {
        cout << "Error during window creation  (SDL)." << endl;
        return 0;
    }
    
    // SDL Renderer Creation
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
        cout << "Error during renderer creation (SDL)." << endl;
        return 0;
    }
    
    // Create an SDL surface to write the noise values to.
    Uint32 rmask, gmask, bmask, amask;
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    
    image = SDL_CreateRGBSurface(SDL_SWSURFACE, WIDTH, HEIGHT, 32, rmask, gmask, bmask, amask);
    if (!image) {
        cout << "Error during surface creation." << endl;
        return 0;
    }
    
    // Generate a noise value for each pixel
    float invWidth = 1.0f / float(WIDTH);
    float invHeight = 1.0f / float(HEIGHT);
    float noise;
    float min = 0.0f;
    float max = 0.0f;
    
    Uint8 colourByte;
    vector<point> points;
    
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            
            // Generate noise value
            noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72);
            
            // Set noise value dependant on hashed value
            int index = HASH(x, y);
            if (PAIRING_FUNCTION == 1 || PAIRING_FUNCTION == 2) {
                indexArray[indexArrayCurr++] = index;
            }
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
    if (PAIRING_FUNCTION == 1 || PAIRING_FUNCTION == 2) {
        
        // FIXME: FOURNIER ANALYSIS
        float *realOut;
        realOut = new float[WIDTH * HEIGHT];
        //realOut = malloc(WIDTH * HEIGHT * sizeof(float));
        float *imgOut;
        imgOut = new float[WIDTH * HEIGHT];
        //imgOut = malloc(WIDTH * HEIGHT * sizeof(float));
        float *ampOut;
        ampOut = new float[WIDTH * HEIGHT];
        //ampOut = malloc(WIDTH * HEIGHT * sizeof(float));
        /*
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < WIDTH; j++) {
                realOut[i][j] = 0.0f;
                imgOut[i][j] = 0.0f;
                ampOut[i][j] = 0.0f;
            }
        }*/
        
        for (int i = 0; i < (HEIGHT * WIDTH); i++) {
            
            int index = indexArray[i];
            int inv_x = INVERT_X(index);
            int inv_y = INVERT_Y(index);
            
            noise = noiseArray[index];
            
            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;
            
            // Ammplitude distribution array
            ampDistributionArray[i] = noise;
            
            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;
            
            // FIXME: Issue with Fournier Analysis Calculation - Currently disabled
            if (ANALYSIS == 1 && FOURNIER == 1) {
                /*
                min = 1;
                max = -1;
                 */
                for (int xSpace = 0; xSpace < WIDTH; xSpace++) {
                    for (int ySpace = 0; ySpace < HEIGHT; ySpace++) {
                        
                        realOut[inv_x + inv_y] += (noise *
                                                  cos(2.0f * PI * ((1.0f * inv_x * xSpace / WIDTH) +
                                                                (1.0f * inv_y * ySpace / HEIGHT)))) / sqrt(WIDTH * HEIGHT);
                        imgOut[inv_x + inv_y] -= (noise * sin(2.0f * PI *
                                                             ((1.0f * inv_x * xSpace / WIDTH) +
                                                              (1.0f * inv_y * ySpace / HEIGHT)))) / sqrt( WIDTH * HEIGHT);
                         
                        ampOut[inv_x + inv_y] = sqrt(realOut[inv_x + inv_y] * realOut[inv_x + inv_y] +
                                                    imgOut[inv_x + inv_y] * imgOut[inv_x + inv_y]);
                        
                        /*
                        if (ampOut[inv_x + inv_y] < min) {
                            min = ampOut[inv_x + inv_y];
                        }
                        
                        if (ampOut[inv_x + inv_y] > max) {
                            max = ampOut[inv_x + inv_y];
                        }
                         */
                    }
                }
                printf("Iteration %d of %d complete. REAL: %f\n", i, HEIGHT * WIDTH, ampOut[inv_x + inv_y]);
                printf("Iteration %d of %d complete. IMAG: %f\n", i, HEIGHT * WIDTH, ampOut[inv_x + inv_y]);
                printf("Iteration %d of %d complete. AMPL: %f\n", i, HEIGHT * WIDTH, ampOut[inv_x + inv_y]);
                
                printf("\nOld noise: %f\n", noise);
                //temp = 1.0f / (max - min);
                //noise = -1.0f + 2.0f * (ampOut[inv_x + inv_y] - min) * temp;
                //printf("New noise: %f\n\n", noise);
                printf("New noise: %f\n\n", ampOut[inv_x + inv_y]);
            }
            
            colourByte = Uint8(noise * 0xff);
            colourPixel(image, inv_x, inv_y, SDL_MapRGB(image -> format, colourByte, colourByte, colourByte));
            
            points.push_back(point());
            points[i].x = inv_x;
            points[i].y = inv_y;
            points[i].colour = noise;
        }
    } else if (PAIRING_FUNCTION == 3) {
        for (int i = 0; i < (HEIGHT * WIDTH); i++) {
            int m = rsInvert(i);
            
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

            // Amplitude distribution array (for analysis purposes)
            ampDistributionArray[i] = noise;
            
            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;
            
            colourByte = Uint8(noise * 0xff);
            colourPixel(image, inv_x, inv_y, SDL_MapRGB(image -> format, colourByte, colourByte, colourByte));
            
            points.push_back(point());
            points[i].x = inv_x;
            points[i].y = inv_y;
            points[i].colour = noise;
        }
    } else {
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                
                int index = HASH(x, y);
                noise = noiseArray[index];
                
                // Use gaussian distribution of noise values to fill [-1, 1] range.
                noise = -1.0f + 2.0f * (noise - min) * temp;
                
                // Amplitude distribution array
                ampDistributionArray[y * WIDTH + x] = noise;
                
                // Remap to RGB friendly colour values in range [0, 1].
                noise += 1.0f;
                noise *= 0.5f;
                
                colourByte = Uint8(noise * 0xff);
                colourPixel(image, x, y, SDL_MapRGB(image -> format, colourByte, colourByte, colourByte));
                
                points.push_back(point());
                int i = x * HEIGHT + y;
                points[i].x = x;
                points[i].y = y;
                points[i].colour = noise;
            }
        }
    }
    
    // Print analysis information and write to CSV when enabled
    if (ANALYSIS) {
        
        char filename[] = "../Analysis/amplitude_out.csv";
        ofstream outFile;
        outFile.open(filename, ios::out | ios::app);
        outFile << "GaussianAmplitude\n";
        
        for (int i = 0; i < (HEIGHT * WIDTH); i++) {
            outFile << ampDistributionArray[i] << "\n";
        }
        outFile.close();
        printf("Written to CSV.\n");
    }
    
    // Print testing data when testing mode is enabled
    if (TESTING) {
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                // Invert Hash Function
                int index = HASH(x, y);
                
                int inv_x = INVERT_X(index);
                int inv_y = INVERT_Y(index);
                
                printf("Hashed Index: %d\n", index);
                printf("Actual X: %d  |  Inverted X: %d\n", x, inv_x);
                printf("Actual Y: %d  |  Inverted Y: %d\n\n", y, inv_y);
            }
        }
    }
    
    // Output image
    if (IMAGE_OUTPUT) {
        
        // Conversion of surface to texture
        imageTexture = SDL_CreateTextureFromSurface(renderer, image);
        if (!imageTexture) {
            cout << "Error during surface to texture conversion." << endl;
            return 0;
        }

        // Write to BMP (won't open on MAC OSX)
        SDL_SaveBMP(image, "../Output/testing.bmp");
        SDL_FreeSurface(image);
        
        // Copy image to frame buffer and display
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
        bool quit = false;
        SDL_Event event;
        int tickDelay = int((1.0 / 25.0) * 1000);
        
        // Quit app on ESC press
        while (!quit) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                        
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                            quit = true;
                }
            }
            SDL_Delay(tickDelay);
        }
        
        // Cleanup & delete unneeded items
        SDL_DestroyTexture(imageTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
    delete[] noiseArray;
    if (PAIRING_FUNCTION == 1 || PAIRING_FUNCTION == 2) {
        delete[] indexArray;
    }
    delete noiseGenerator;
    
    return 0;
}

/**
 *
 *
 */
int performAnalysis(int currentIteration) {
    
    // Initialize noise
    Fractal *noiseGenerator = new Fractal();
    noiseGenerator -> setInitFrequency(4.0f);
    
    // Define array size
    unsigned long long int arr_size = pow(WIDTH, 2) * pow(HEIGHT, 2);
    int *indexArray = new int[WIDTH * HEIGHT];
    int indexArrayCurr = 0;
    
    // Intialize nosie array
    float *noiseArray = new float[arr_size];
    
    // Initialize Amplitude Distribution Array
    float *ampDistributionArray = new float[WIDTH * HEIGHT];
    
    // Generate a noise value for each pixel
    float invWidth = 1.0f / float(WIDTH);
    float invHeight = 1.0f / float(HEIGHT);
    float noise;
    float min = 0.0f;
    float max = 0.0f;
    
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            
            // Generate noise value
            noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72);
            
            // Set noise value dependant on hashed value
            int index = HASH(x, y);
            if (PAIRING_FUNCTION == 1 || PAIRING_FUNCTION == 2) {
                indexArray[indexArrayCurr++] = index;
            }
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
    if (PAIRING_FUNCTION == 1 || PAIRING_FUNCTION == 2) {
        for (int i = 0; i < (HEIGHT * WIDTH); i++) {
            
            int index = indexArray[i];
            int inv_x = INVERT_X(index);
            int inv_y = INVERT_Y(index);
            
            noise = noiseArray[index];
            
            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;
            
            // Amplitude distribution array (for analysis purposes)
            ampDistributionArray[i] = noise;
            
            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;
        }
    } else if (PAIRING_FUNCTION == 3) {
        for (int i = 0; i < (HEIGHT * WIDTH); i++) {
            int m = rsInvert(i);
            
            int inv_x;
            int inv_y;
            if ((i - pow(m, 2)) < m) {
                inv_x = i - pow(m, 2);
                inv_y = i;
            } else {
                inv_x = i;
                inv_y = pow(m, 2) + (2*m) - i;
            }
            
            noise = noiseArray[i];
            
            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;
            
            // Amplitude distribution array (for analysis purposes)
            ampDistributionArray[i] = noise;
            
            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;
        }
    } else {
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                
                int index = HASH(x, y);
                noise = noiseArray[index];
                
                // Use gaussian distribution of noise values to fill [-1, 1] range.
                noise = -1.0f + 2.0f * (noise - min) * temp;
                
                // Amplitude distribution array (for analysis purposes)
                ampDistributionArray[y * WIDTH + x] = noise;
                
                // Remap to RGB friendly colour values in range [0, 1].
                noise += 1.0f;
                noise *= 0.5f;
            }
        }
    }
    
    // Print out and write analysis information to CSV when enabled
    
    char filename[] = "../Analysis/amplitude_out.csv";
    ofstream outFile;
    outFile.open(filename, ios::out | ios::app);
    if (currentIteration == 0) {
        outFile << "GaussianAmplitude\n";
    }
    
    for (int i = 0; i < (HEIGHT * WIDTH); i++) {
        outFile << ampDistributionArray[i] << "\n";
    }
    outFile.close();
    printf("Iteration[%d] written to CSV.\n", currentIteration);
    
    // Print out testing information when enabled
    if (TESTING) {
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                // Invert Hash Function
                int index = HASH(x, y);
                
                int inv_x = INVERT_X(index);
                int inv_y = INVERT_Y(index);
                
                printf("Hashed Index: %d\n", index);
                printf("Actual X: %d  |  Inverted X: %d\n", x, inv_x);
                printf("Actual Y: %d  |  Inverted Y: %d\n\n", y, inv_y);
            }
        }
    }
    
    delete[] noiseArray;
    delete[] indexArray;
    delete noiseGenerator;
    
    return 0;
}

/**
 *
 *
 */
int performAnalysis(int currOctave, int currLacunarity, int currPersistence) {
    
    // Initialize noise
    Fractal *noiseGenerator = new Fractal();
    noiseGenerator -> setInitFrequency(4.0f);
    
    float currLac = 1.5f + 0.25f*currLacunarity;
    float currPer = 0.45f + 0.05f*currPersistence;
    
    noiseGenerator -> setOctaves(currOctave);
    noiseGenerator -> setLacunarity(currLac);
    noiseGenerator -> setPersistence(currPer);
    
    // Define array size
    unsigned long long int arr_size = pow(WIDTH, 2) * pow(HEIGHT, 2);
    int *indexArray = new int[WIDTH * HEIGHT];
    int indexArrayCurr = 0;
    
    // Intialize nosie array
    float *noiseArray = new float[arr_size];
    
    // Initialize Amplitude Distribution Array
    float *ampDistributionArray = new float[WIDTH * HEIGHT];
    
    // Generate a noise value for each pixel
    float invWidth = 1.0f / float(WIDTH);
    float invHeight = 1.0f / float(HEIGHT);
    float noise;
    float min = 0.0f;
    float max = 0.0f;
    
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            
            // Generate noise value
            noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72);
            
            // Set noise value dependant on hashed value
            int index = HASH(x, y);
            
            if (PAIRING_FUNCTION == 1 || PAIRING_FUNCTION == 2) {
                indexArray[indexArrayCurr++] = index;
            }
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
    if (PAIRING_FUNCTION == 1 || PAIRING_FUNCTION == 2) {
        for (int i = 0; i < (HEIGHT * WIDTH); i++) {
            
            int index = indexArray[i];
            int inv_x = INVERT_X(index);
            int inv_y = INVERT_Y(index);
            
            noise = noiseArray[index];
            
            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;
            
            // Amplitude distribution array (for analysis purposes)
            ampDistributionArray[i] = noise;
            
            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;
        }
    } else if (PAIRING_FUNCTION == 3) {
        
        for (int i = 0; i < (HEIGHT * WIDTH); i++) {
            int m = rsInvert(i);
            
            int inv_x;
            int inv_y;
            if ((i - pow(m, 2)) < m) {
                inv_x = i - pow(m, 2);
                inv_y = i;
            } else {
                inv_x = i;
                inv_y = pow(m, 2) + (2*m) - i;
            }
            
            noise = noiseArray[i];
            
            // Use gaussian distribution of noise values to fill [-1, 1] range.
            noise = -1.0f + 2.0f * (noise - min) * temp;
            
            // Amplitude distribution array (for analysis purposes)
            ampDistributionArray[i] = noise;
            
            // Remap to RGB friendly colour values in range [0, 1].
            noise += 1.0f;
            noise *= 0.5f;
        }
    } else {
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                
                int index = HASH(x, y);
                noise = noiseArray[index];
                
                // Use gaussian distribution of noise values to fill [-1, 1] range.
                noise = -1.0f + 2.0f * (noise - min) * temp;
                
                // Amplitude distribution array (for analysis purposes)
                ampDistributionArray[y * WIDTH + x] = noise;
                
                // Remap to RGB friendly colour values in range [0, 1].
                noise += 1.0f;
                noise *= 0.5f;
            }
        }
    }
    
    // Print Analysis information and save as CSV
    char filename[] = "../Analysis/amplitude_out.csv";
    ofstream outFile;
    outFile.open(filename, ios::out | ios::app);
    
    if (currOctave == 1 && currLacunarity == 0 && currPersistence == 0) {
        outFile << "GaussianAmplitude\n";
    }
    
    for (int i = 0; i < (HEIGHT * WIDTH); i++) {
        outFile << ampDistributionArray[i] << "\n";
    }
    outFile.close();
    printf("Iteration[%d | %f | %f] written to CSV.\n", currOctave, currLac, currPer);
    
    // Print testing values when testing mode is enabled
    if (TESTING) {
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                // Invert Hash Function
                int index = HASH(x, y);
                
                int inv_x = INVERT_X(index);
                int inv_y = INVERT_Y(index);
                
                printf("Hashed Index: %d\n", index);
                printf("Actual X: %d  |  Inverted X: %d\n", x, inv_x);
                printf("Actual Y: %d  |  Inverted Y: %d\n\n", y, inv_y);
            }
        }
    }
    
    delete[] noiseArray;
    delete[] indexArray;
    delete noiseGenerator;
    
    return 0;
}


#undef main

/**
 *
 *
 */
int main() {

    if (IMAGE_OUTPUT) {
        generateImage();
    } else if (ANALYSIS) {
        if (ANALYSIS_TYPE == 0) {
            for (int loop = 0; loop < 1; loop++) {
                performAnalysis(loop);
            }
        } else if (ANALYSIS_TYPE == 1) {
            int octaveStart = 4;
            int octaveEnd = 8;
            int lacunarityStart = 0;
            int lacunarityEnd = 2;
            int persistenceStart = 0;
            int persistenceEnd = 2;
            
            for (octaveStart = 1; octaveStart <= octaveEnd; octaveStart++) {
                for (lacunarityStart = 0; lacunarityStart <= lacunarityEnd; lacunarityStart++) {
                    for (persistenceStart = 0; persistenceStart <= persistenceEnd; persistenceStart++) {
                        performAnalysis(octaveStart, lacunarityStart, persistenceStart);
                    }
                }
            }
        }
    }
    
    return 0;
}

