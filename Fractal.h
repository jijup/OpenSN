/*
 * Fractal.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 * 
 * Fractal Brownian motion via sum of Perlin noise octaves.
 */

#ifndef _FRACTAL_H_
#define _FRACTAL_H_

#include "NoiseTypes/Perlin.h"
#include "NoiseTypes/Gabor.h"
#include "NoiseTypes/Marble.h"
#include "NoiseTypes/Worley.h"
#include "NoiseTypes/ExperimentalNoise.h"
#include "NoiseTypes/Splatter.h"
#include "NoiseTypes/Wood.h"
#include "NoiseTypes/PrimeGradient.h"
#include "NoiseTypes/PrimeGradientDensity.h"
#include "NoiseTypes/BetterGradient.h"
#include "NoiseTypes/Wavelet.h"
#include "NoiseTypes/Phasor.h"

class Fractal {
public:
    Fractal();
	Fractal(int noiseType);
	~Fractal();

	// Given (X, Y, Z), 3D coordinates, returns a noise value in the range [-1, 1]
	float noise(float xCoord, float yCoord, float zCoord);

	// Sets the number of octaves
	void setOctaves(int o);

	// Sets the lacunarity for each octave (ideally [2, inf]).
	void setLacunarity(float l);

	// Sets the persistence for each octave (ideally [0.0, 0.5] or [0.0, 1.0]).
	void setPersistence(float p);

	// Sets the initial value for frequency and amplitude.
	void setInitFrequency(float f);
	void setInitAmplitude(float f);

    // Sets width and height within Perlin object
	void setPerlinDimensions(int width, int height);

	//
	void setPGNOctaves(int numOctaves);

	// Sets hashing mechanism
	void setPairingFunction(int pairingFunction);
    void setPairingFunctionMarble(int pairingFunction);
    void setPairingFunctionExperimental(int pairingFunction);
    void setPairingFunctionSplatter(int pairingFunction);
    void setPairingFunctionWood(int pairingFunction);

	int noiseType;

    Perlin *perlinSource;
    PrimeGradient *primeSource;
    PrimeGradientDensity *primeDensitySource;
    Gabor *gaborSource;
    Marble *marbleSource;
    Worley *worleySource;
    ExperimentalNoise *experimentalSource;
    Splatter *valueSplatterSource;
    Wood *valueWoodSource;
    BetterGradient *betterGradientSource;
    Wavelet *waveletSource;
    Phasor *phasorSource;

private:
	/*Perlin *perlinSource;
	PrimeGradient *primeSource;
	PrimeGradientDensity *primeDensitySource;
	Gabor *gaborSource;
	Marble *marbleSource;
	Worley *worleySource;
	ExperimentalNoise *experimentalSource;
	Splatter *valueSplatterSource;
	Wood *valueWoodSource;
	BetterGradient *betterGradientSource;
	Wavelet *waveletSource;
	Phasor *phasorSource;*/

	int octaves; // Number of octaves (default is 8).
	float lacunarity; // Frequency for each octave (default is 2.0).
	float persistence; // Amplitude for each octave (default is 0.5).
	float initFrequency; // Initial frequency (default of 1.0).
	float initAmplitude; // Initial amplitude (default is 1.0)

	float min;
	float max;
};

#endif

