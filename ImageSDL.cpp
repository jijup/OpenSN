/**
 * ImageSDL.cpp
 * Authors: Sheldon Taylor, Jiji Poovvancheri
 *
 * SDL based implementation of saving and rendering images.
 */

#include "ImageSDL.h"

ImageSDL::ImageSDL(){}

ImageSDL::~ImageSDL(){};

/*
 * Saves image as BMP file and/or renders image in SDL, depending on user provided parameters.
 *
 * Parameters:
 *      points: Vector of point structs
 *      writeBMP: 0 being do no create BMP and 1 being create BMP
 *      displayImage: 0 being do no display and 1 being display
 *      width: pixels in x-dimension
 *      height: pixels in y-dimension
 *      title: pairing method used
 */
void ImageSDL::renderImage(std::vector<Noise::Point> points, int writeBMP, int displayImage, int width, int height, std::string title) {

    // Convert title to character array
    int titleLength = title.length();
    char titleCharArray[titleLength + 1];
    strcpy(titleCharArray, title.c_str());

    // Initialize SDL window, renderer, image and texture
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *image = NULL;
    SDL_Texture *imageTexture = NULL;

    // SDL Window Creation
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error during SDL initialization." << std::endl;
        // TODO: Throw error
        //return 0;
    }
    
    window = SDL_CreateWindow(titleCharArray, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        std::cout << "Error during window creation  (SDL)." << std::endl;
        // TODO: Throw error
        //return 0;
    }
    
    // SDL Renderer Creation
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
        std::cout << "Error during renderer creation (SDL)." << std::endl;
        // TODO: Throw error
        //return 0;
    }
    
    // Create an SDL surface to write the noise values to.
    Uint32 rmask, gmask, bmask, amask;
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;

    image = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);
    if (!image) {
        std::cout << "Error during surface creation." << std::endl;
        // TODO: Throw error
        //return 0;
    }

    Uint8 colourByte;

    // Loop through points and assign noise values to SDL image
    for (int i = 0; i < points.size(); i++) {
        colourByte = Uint8(points[i].colour * 0xff);
        colourPixel(image, points[i].x, points[i].y, SDL_MapRGB(image -> format, colourByte, colourByte, colourByte));
    }

    // Conversion of surface to texture
    imageTexture = SDL_CreateTextureFromSurface(renderer, image);
    if (!imageTexture) {
        std::cout << "Error during surface to texture conversion." << std::endl;
        // TODO: Throw error
        //return 0;
        }

    if (writeBMP == 1) {
        // Write to BMP (won't open on MAC OSX)
        SDL_SaveBMP(image, "../Output/testing.bmp");
    }

    SDL_FreeSurface(image);

    if (displayImage == 1) {
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
    }
    
    // Cleanup & delete unneeded items
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
