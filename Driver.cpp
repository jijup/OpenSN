/* 
 * Driver.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Driver for the implementation of Perlin noise via various hashing/pairing functions.
 */

#include <SDL.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Fractal.h"

using namespace std;

#define TESTING 0	// Testing mode off
//#define TESTING 1	// Testing mode on

//#define ANALYSIS 0	// Analysis mode off
#define ANALYSIS 1	// Analysis mode on

#define WIDTH 1000	// X Resolution
#define HEIGHT 750	// Y Resolution

// Define Pairing Function to be used (uncomment selected PAIRING_FUNCTION)
#define PAIRING_FUNCTION 0 	// Linear
//#define PAIRING_FUNCTION 1 	// Cantor
//#define PAIRING_FUNCTION 2 	// Szudzik


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

// Colours pixel at given position, (x, y). Assumes 32 bits per pixel.
void colourPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
	Uint32 *p = (Uint32 *)surface -> pixels + y * surface -> w + x;
	*p = pixel;
}

#if PAIRING_FUNCTION == 0	// Linear
	#define TITLE 		"Perlin Noise - Linear" 
	#define HASH(x, y)  	linearPair(x, y)
	#define INVERT_X(z)	1
	#define INVERT_Y(z)	1
#elif PAIRING_FUNCTION == 1	// Cantor
	#define TITLE 		"Perlin Noise - Cantor"
	#define HASH(x, y)  	cantorPair(x, y)
	#define INVERT_X(z)	cantorInvertX(z)
	#define INVERT_Y(z)	cantorInvertY(z)
#elif PAIRING_FUNCTION == 2	// Szudzik
	#define TITLE 		"Perlin Noise - Szudzik"
	#define HASH(x, y)  	szudzikPair(x, y)
	#define INVERT_X(z)	szudzikInvertX(z)
	#define INVERT_Y(z)	szudzikInvertY(z)
#else				// Other
	#define TITLE 		"Perlin Noise - Other"
	#define HASH(x, y)  	(y * WIDTH + x)
#endif

#undef main

int main() {

	// Define array size
	unsigned long long int arr_size = pow(WIDTH, 2) * pow(HEIGHT, 2);
	int *indexArray = new int[WIDTH * HEIGHT];
	int indexArrayCurr = 0;

	// Initialize noise
	Fractal *noiseGenerator = new Fractal();
	noiseGenerator -> setInitFrequency(4.0f);

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

	for (int x = 0; x < WIDTH; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {

			// Generate noise value 
			noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72);
	
			// Set noise value dependant on hashed value
			int index = HASH(x, y);
			indexArray[indexArrayCurr++] = index;
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

			// FOR ANALYSIS PURPOSES - AMPLITUDE DISTRIBUTION
			ampDistributionArray[i] = noise;
		
			// Remap to RGB friendly colour values in range [0, 1].
			noise += 1.0f;
			noise *= 0.5f;

			colourByte = Uint8(noise * 0xff);
			colourPixel(image, inv_x, inv_y, SDL_MapRGB(image -> format, colourByte, colourByte, colourByte));
		}
	} else {
		for (int x = 0; x < WIDTH; ++x) {
			for (int y = 0; y < HEIGHT; ++y) {
				
				int index = HASH(x, y);
				noise = noiseArray[index];
			
				// Use gaussian distribution of noise values to fill [-1, 1] range.
				noise = -1.0f + 2.0f * (noise - min) * temp;
		
				// FOR ANALYSIS PURPOSES - AMPLITUDE DISTRIBUTION
				ampDistributionArray[y * WIDTH + x] = noise;
			
				// Remap to RGB friendly colour values in range [0, 1].
				noise += 1.0f;
				noise *= 0.5f;
			
				colourByte = Uint8(noise * 0xff);
				colourPixel(image, x, y, SDL_MapRGB(image -> format, colourByte, colourByte, colourByte));
			}
		}
	}	

	// FOR ANALYSIS PURPOSES
	if (ANALYSIS) {
		ofstream outFile;
		outFile.open("../Analysis/amplitude_out.csv");
		outFile << "GaussianAmplitude\n";
		for (int i = 0; i < (HEIGHT * WIDTH); i++) {
			outFile << ampDistributionArray[i] << "\n";
		}
		outFile.close();
	}
	
	// FOR TESTING PURPOSES
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

	// Conversion of surface to texture
	imageTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (!imageTexture) {
		cout << "Error during surface to texture conversion." << endl;
		return 0;
	}

	// FIXME: IMPLEMENT WRITE TO BMP/PNG
	//SDL_SaveBMP(image, "out.bmp");
	
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

	delete[] noiseArray;
	delete[] indexArray;
	delete noiseGenerator;
	
	return 0;
}

