/* 
 * driver.cpp
 * Sheldon Taylor
 * 
 * Based on Chris Little's implementation of Perlin Noise (used primarily for SDL2 implementation). 
 */

#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include "Fractal.h"

using namespace std;

// Colours pixel at given position, (x, y). Assumes 32 bits per pixel.
void colourPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
	Uint32 *p = (Uint32 *)surface -> pixels + y * surface -> w + x;
	*p = pixel;
}

#undef main

int main() {
	//int width = 1000;
	int width = 400;
	//int height = 750;
	int height = 300;

	// Initialize noise
	Fractal *noiseGenerator = new Fractal();
	noiseGenerator -> setInitFrequency(4.0f);

	// Initialize data structure to store noise
	//int arraySize = width * height;  // Linear (N)
	int arraySize = width * width * height * height;  // Cantor Pairing (NxN)	
	float *noiseArray = new float[arraySize];

	// Initialize SDL window, renderer, image and texture
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *image = NULL;
	SDL_Texture *imageTexture = NULL;

	// Create an SDL window and renderer.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL couldn't init." << endl;
		return 1;
	}

	window = SDL_CreateWindow("Perlin Noise", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (!window) {
		cout << "SDL couldn't create window." << endl;
		return 2;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (!renderer) {
		cout << "SDL couldn't retrieve the renderer." << endl;
		return 3;
	}


	// Create an SDL surface to write the noise values to.
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIGENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	image = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);
	if (!image) {
		cout << "Failed to create surface." << endl;
		return 4;
	}

	// Generate a noise value for each pixel
	float invWidth = 1.0f / float(width);
	float invHeight = 1.0f / float(height);
	float noise;
	float min = 0.0f;
	float max = 0.0f;
	//int index;
	//vector<int> indexVec;
	int *indexSetArray = new int[arraySize];
	int *indexGetArray = new int[arraySize];
	Uint8 colourByte;

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {

			noise = noiseGenerator -> noise(float(x) * invWidth, float(y) * invHeight, 0.72);
	
			// Initial Hash Function
			//int index = y * width + x;

			// Cantor Pairing Function
			int index = ((x + y) * (x + y + 1)) / 2 + y;

			// TO DO: IMPLEMENT SZUDZIK PAIRING FUNCITON
			//
			//
			
			noiseArray[index] = noise;
			indexSetArray[index] = index;
	
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

	// TO DO: IMPLEMENT INVERSION OF CANTOR/SZUDZIK PAIRING FUNCITONS
	//
	//

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {

			// Use gaussian distribution of noise values to fill [-1, 1] range.
			
			// Initial Hash Function
			//int index = y * width + x;

			// Cantor Pairing Function
			int index = ((x + y) * (x + y + 1)) / 2 + y;
			
			//cout << index << endl;
			noise = noiseArray[index];
			indexGetArray[index] = index;

			noise = -1.0f + 2.0f * (noise - min) * temp;
		
			// Remap to RGB friendly colour values in range [0, 1].
			noise += 1.0f;
			noise *= 0.5f;

			colourByte = Uint8(noise * 0xff);

			colourPixel(image, x, y, SDL_MapRGB(image -> format, colourByte, colourByte, colourByte));
		}
	}

	// FOR TESTING PURPOSES ONLY
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			
			//int index = y * width + x; // Initial function (linear)
			int index = ((x + y) * (x + y + 1)) / 2 + y; // Cantor Pairing Function
			
			cout << "x: " << x << "y: " << y << " | indexSet: " << indexSetArray[index] << " | indexGet: " << indexGetArray[index] << endl;
		}
	}


	// Convert surface to texture that can be copied to the window.
	imageTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (!imageTexture) {
		cout << "Failed to convert surface to texture." << endl;
		return 5;
	}

	SDL_FreeSurface(image);

	// Copy image to frame buffer and display
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

	bool quit = false;
	SDL_Event event;
	int tickDelay = int((1.0 / 25.0) * 1000);

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
                
				case SDL_KEYDOWN:
                    			// Quit on escape pressed
                    			if (event.key.keysym.sym == SDLK_ESCAPE)
                        		quit = true;
			}
		}

		SDL_Delay(tickDelay);
	}

	// Cleanup
	SDL_DestroyTexture(imageTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	delete[] noiseArray;
	delete[] indexSetArray;
	delete[] indexGetArray;
	delete noiseGenerator;

	return 0;
}

