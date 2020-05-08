/**
 * Fractal.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * fBm Implementation.
 */

#include "Fractal.h"

Fractal::Fractal() {}

Fractal::Fractal(int noiseType) {

    this->noiseType = noiseType;

    this->perlinSource = new Perlin();
    this->gaborSource = new Gabor();
    this->marbleSource = new Marble();
    this->worleySource = new Worley();
    this->curlSource = new Curl();

    this->octaves = 8;
    this->lacunarity = 2.0f;
    this->persistence = 0.5f;
    this->initFrequency = 2.0f;
    this->initAmplitude = 1.0f;
}

Fractal::~Fractal() {
	delete this->perlinSource;
    delete this->gaborSource;
    delete this->marbleSource;
}

float Fractal::noise(float xCoord, float yCoord, float zCoord) {
	float sum = 0;
	float freq = this->initFrequency;
	float amp = this->initAmplitude;

	for (int i = 0; i < this->octaves; i++) {

	    if (this->noiseType == 0) {           // Perlin
            sum += this->perlinSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            freq *= this->lacunarity;
            amp *= this->persistence;
        } else if (this->noiseType == 1) {    // Gabor
            sum += this->gaborSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            // FIXME: REMOVE?
            if (this->octaves == 1) {
                break;
            } else {
                freq *= this->lacunarity;
                amp *= this->persistence;
            }
	    } else if (this->noiseType == 2) {    // Marble
            sum = this->marbleSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            break;
	    } else if (this->noiseType == 3) {    // Worley
            sum = this->worleySource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            break;
        } else if (this->noiseType == 4) {    // Curl
            sum = this->curlSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            break;
        } else {
	        // TODO: Throw error
	    }
	}

	return sum;
}

void Fractal::setOctaves(int o) {
	if (o > 0) {
        this->octaves = o;
	}
}

void Fractal::setPersistence(float p) {
    this->persistence = p;
}

void Fractal::setLacunarity(float l) {
    this->lacunarity = l;
}

void Fractal::setInitFrequency(float f) {
    this->initFrequency = f;
}

void Fractal::setInitAmplitude(float a) {
    this->initAmplitude = a;
}

