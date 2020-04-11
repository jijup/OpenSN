/*
 * Fractal.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * fBm Implementation.
 */

#include "Fractal.h"

Fractal::Fractal() {}

Fractal::Fractal(int noiseType) {

    this -> noiseType = noiseType;

    perlinSource = new Perlin();
    marbleSource = new Marble();

	octaves = 8;
	lacunarity = 2.0f;
	persistence = 0.5f;
	initFrequency = 2.0f;
	initAmplitude = 1.0f;
}

Fractal::~Fractal() {
	delete perlinSource;
    //delete gaborSource;
    delete marbleSource;
}

float Fractal::noise(float xCoord, float yCoord, float zCoord) {
	float sum = 0;
	float freq = initFrequency;
	float amp = initAmplitude;

	for (int i = 0; i < octaves; i++) {

	    if (noiseType == 0) {
            sum += perlinSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            freq *= lacunarity;
            amp *= persistence;
        } else if (noiseType == 1) {
            sum += perlinSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            freq *= lacunarity;
            amp *= persistence;
	    } else if (noiseType == 2) {
            sum += marbleSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            //freq *= lacunarity;
            //amp *= persistence;
	    } else {
	        // TODO: Throw error
	    }
	}

	return sum;
}

void Fractal::setOctaves(int o) {
	if (o > 0) {
		octaves = o;
	}
}

void Fractal::setPersistence(float p) {
	persistence = p;
}

void Fractal::setLacunarity(float l) {
	lacunarity = l;
}

void Fractal::setInitFrequency(float f) {
	initFrequency = f;
}

void Fractal::setInitAmplitude(float a) {
	initAmplitude = a;
}

