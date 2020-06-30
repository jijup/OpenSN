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
    this->primeSource = new PrimeGradient();
    this->primeDensitySource = new PrimeGradientDensity();
    this->gaborSource = new Gabor();
    this->marbleSource = new Marble();
    this->worleySource = new Worley();
    this->experimentalSource = new ExperimentalNoise();
    this->valueSplatterSource = new Splatter();
    this->valueWoodSource = new Wood();
    this->betterGradientSource = new BetterGradient();
    this->waveletSource = new Wavelet();
    this->phasorSource = new Phasor();

    this->octaves = 8;
    this->lacunarity = 2.0f;
    this->persistence = 0.5f;
    this->initFrequency = 2.0f;
    this->initAmplitude = 1.0f;
}

Fractal::~Fractal() {
	delete this->perlinSource;
	delete this->primeSource;
    delete this->primeDensitySource;
    delete this->gaborSource;
    delete this->marbleSource;
    delete this->worleySource;
    delete this->experimentalSource;
    delete this->valueSplatterSource;
    delete this->valueWoodSource;
    delete this->betterGradientSource;
    delete this->waveletSource;
    delete this->phasorSource;
}

float Fractal::noise(float xCoord, float yCoord, float zCoord) {
	float sum = 0;
	float tempSum = 0;
	float newSum = 0;
    float freq = this->initFrequency;
	float amp = this->initAmplitude;

    float previousValue;

	for (int i = 0; i < this->octaves; i++) {

	    if (this->noiseType == 0) {           // Perlin
            sum += this->perlinSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            freq *= this->lacunarity;
            amp *= this->persistence;
        } else if (this->noiseType == 1) {    // Gabor
            /*if (xCoord == 0 && yCoord == 0 && i == 0) {
                this->octaves = 1;
            }*/

	        sum += this->gaborSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;
            break;

            freq *= this->lacunarity;
            amp *= this->persistence;
	    } else if (this->noiseType == 2) {    // Marble
            sum = this->marbleSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            break;
	    } else if (this->noiseType == 3) {    // Worley
            if (xCoord == 0 && yCoord == 0 && i == 0) {
                printf("    Number of cells being generated: %d.\n", this->worleySource->getNumberOfCells());
                this->octaves = 1;
            }

            sum += this->worleySource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;
            freq *= this->lacunarity;
            amp *= this->persistence;
        } else if (this->noiseType == 4) {    // Experimental Noise
	        if (xCoord == 0 && yCoord == 0 && i == 0) {
                printf("    Number of Bezier curves being generated: %d.\n", this->experimentalSource->getNumberOfCurves());
                this->octaves = 1;
	        }

            sum += this->experimentalSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            freq *= this->lacunarity;
            amp *= this->persistence;
        } else if (this->noiseType == 5) {    // Perlin (splatter)
            sum = this->valueSplatterSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            break;
        } else if (this->noiseType == 6) {    // Perlin (wood)
            sum = this->valueWoodSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            break;
        } else if (this->noiseType == 7) {    // Prime Gradient

            this->primeSource->updateCurrentOctave(i);
            float increment = this->primeSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;
            sum += increment;

            /*int hybrid = 0;     // 0 - additive | 1 - multiplicative
            if (hybrid == 0) {
                float increment = this->primeSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

                sum += increment;

                // fBm Octave Composition Helper
                int octaveTest = 3;
                if (i == octaveTest) {
                    tempSum = increment;
                }

                // Hybrid
                if (i == 0) {
                    newSum += increment;
                } else {
                    float incrementTemp = sum * increment;
                    newSum += incrementTemp;
                }


            } else {
                float increment = this->primeSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

                if (i == 0) {
                    sum += increment;
                } else {
                    increment *= sum;
                    sum += increment;
                }

                // fBm Octave Composition Helper
                int octaveTest = 3;
                if (i == octaveTest) {
                    tempSum = increment;
                }
            }*/

            freq *= this->lacunarity;
            amp *= this->persistence;
        } else if (this->noiseType == 8) {    // Prime Density
            sum += this->primeDensitySource->noise(xCoord, yCoord, zCoord);
            sum += this->primeSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;
	        break;

            /*sum += this->primeSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            freq *= this->lacunarity;
            amp *= this->persistence;*/
        } else if (this->noiseType == 9) {
            sum += this->betterGradientSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            freq *= this->lacunarity;
            amp *= this->persistence;
	    } else if (this->noiseType == 10) {
            sum += this->waveletSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;

            freq *= this->lacunarity;
            amp *= this->persistence;
        } else if (this->noiseType == 11) {
            sum += this->phasorSource->noise(xCoord * freq, yCoord * freq, zCoord * freq) * amp;
            break;

            freq *= this->lacunarity;
            amp *= this->persistence;
        } else {
	        // TODO: Throw error
	    }
	}

	//return tempSum; // fBm Octave Composition Helper

	return sum; // 1
	//return sin(abs(sum)); // 2 (marble)
	//return 1.0f - abs(sum); // 3
    //return abs(sum); // 4
}

void Fractal::setPerlinDimensions(int width, int height) {
    this->perlinSource->setDimensions(width, height);
}

void Fractal::setPairingFunction(int pairingFunction) {
    this->perlinSource->setPairingFunction(pairingFunction);
}

void Fractal::setPairingFunctionMarble(int pairingFunction) {
    this->marbleSource->setPairingFunction(pairingFunction);
}

void Fractal::setPairingFunctionExperimental(int pairingFunction) {
    this->experimentalSource->setPairingFunction(pairingFunction);
}

void Fractal::setPairingFunctionSplatter(int pairingFunction) {
    this->valueSplatterSource->setPairingFunction(pairingFunction);
}

void Fractal::setPairingFunctionWood(int pairingFunction) {
    this->valueWoodSource->setPairingFunction(pairingFunction);
}

void Fractal::setPGNOctaves(int numOctaves) {
    this->primeSource->setNumOctaves(numOctaves);
    //this->primeSource->generatePrimeTable();
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

