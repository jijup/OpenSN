/**
 * ImageOutput.cpp
 * Authors: Sheldon Taylor, Jiji Poovvancheri
 *
 * STB based implementation of saving and rendering images.
 */

#include "ImageOutput.h"

ImageOutput::ImageOutput(){}

ImageOutput::~ImageOutput(){};

/*
 * Saves image as BMP file, if enabled in driver.
 *
 * Parameters:
 *      points: Vector of point structs
 *      writeBMP: 0 being do no create BMP and 1 being create BMP
 *      width: pixels in x-dimension
 *      height: pixels in y-dimension
 */
void ImageOutput::saveBMP(std::vector<Noise::Point> points, int writeBMP, int width, int height, std::string file) {

    if (writeBMP == 1) {
        uint8_t colourByte;

        // Loop through points and assign noise values to RGB array
        unsigned char rgb[width][height];
        for (int i = 0; i < points.size(); i++) {
            colourByte = uint8_t(points[i].colour * 0xff);
            rgb[points[i].x][points[i].y] = colourByte;
        }

        std::string filename = "../Output/Noise/" + file + ".bmp";
        std::string filenameTemp = "../Output/temp/noise_output.bmp";

        int numChannels = 3;
        unsigned char data[width * height * numChannels];

        int arrayIndex = 0;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                data[arrayIndex++] = rgb[i][j];
            }
        }

        printf("\nAttempting to write noise as BMP.\n");

        stbi_write_bmp(filename.c_str(), width, height, 1, data);
        printf("    BMP written: %s\n", filename.c_str());

        stbi_write_bmp(filenameTemp.c_str(), width, height, 1, data);
        printf("    BMP written: %s\n", filenameTemp.c_str());
        printf("Successfully wrote noise as BMP.\n");
    }
}
