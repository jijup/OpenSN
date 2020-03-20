/*
 * Fractal.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * fBm Implementation.
 */

#include "Fractal.h"

Fractal::Fractal() {
	perlinSource = new Perlin();

	octaves = 8;
	lacunarity = 2.0f;
	persistence = 0.5f;
	initFrequency = 2.0f;
	initAmplitude = 1.0f;
}

Fractal::~Fractal() {
	delete perlinSource;
}

float Fractal::noise(float xCoord, float yCoord, float zCoord) {
	float sum = 0;
	float freq = initFrequency;
	float amp = initAmplitude;

	for (int i = 0; i < octaves; i++) {
		sum += perlinSource -> noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

		freq *= lacunarity;
		amp *= persistence;
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

