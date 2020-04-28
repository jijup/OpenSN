/*
 * ImageOutput.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * SDL-based implementation for saving and rendering images.
 */

#include "Noise.h"
#include <iostream>
#include <fstream>
#include <string>

#include <stb_image/stb_image.h>
#include <stb_image/stb_image_write.h>

#ifndef _IMAGEOUTPUT_H_
#define _IMAGEOUTPUT_H_

class ImageOutput {
public:
    ImageOutput();
    ~ImageOutput();
    
    /// Saves as BMP file
    void saveBMP(std::vector<Noise::Point> points, int writeBMP, int width, int height, std::string file);
};

#endif

