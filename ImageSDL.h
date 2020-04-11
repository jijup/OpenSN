/*
 * ImageSDL.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * SDL-based implementation for saving and rendering images.
 */

#include "Noise.h"
#include <SDL.h>    // CMake
#include <iostream>
#include <fstream>
#include <string>
//#include <SDL2/SDL.h>    // Makefile

#ifndef _IMAGESDL_H_
#define _IMAGESDL_H_

class ImageSDL {
public:
    ImageSDL();
    ~ImageSDL();
    
    /// Colours pixel at given position, (x, y). Assumes 32 bits per pixel.
    void colourPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
        Uint32 *p = (Uint32 *)surface -> pixels + y * surface -> w + x;
        *p = pixel;
    }
    
    /// Given (X, Y, Z), 3D coordinates, returns a noise value in the range [-1, 1]
    void renderImage(std::vector<Noise::Point> points, int writeBMP, int displayImage, int width, int height, std::string title);
};

#endif

