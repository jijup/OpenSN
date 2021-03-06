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

        int grayscale = 1;
        int colored = 1;

        if (grayscale == 1) {
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

            if (colored == 0) {
                std::string filename = "../Output/Noise/" + file + "_Colour.bmp";
                std::string filenameTemp = "../Output/temp/noise_output_col.bmp";

                printf("\nAttempting to write greyscale noise as BMP in place of coloured output.\n");

                stbi_write_bmp(filename.c_str(), width, height, 1, data);
                printf("    BMP written: %s\n", filename.c_str());

                stbi_write_bmp(filenameTemp.c_str(), width, height, 1, data);
                printf("    BMP written: %s\n", filenameTemp.c_str());
                printf("Successfully wrote noise as BMP.\n");
            }
        }

        if (colored == 1) {
            uint8_t colourByte;

            // Loop through points and assign noise values to RGB array
            unsigned char rgb[width][height];
            for (int i = 0; i < points.size(); i++) {
                //colourByte = uint8_t(points[i].colour * 0xff);
                colourByte = uint8_t(points[i].colour * 0xff);
                rgb[points[i].x][points[i].y] = colourByte;
            }

            std::string filename = "../Output/Noise/" + file + "_Colour.bmp";
            std::string filenameTemp = "../Output/temp/noise_output_col.bmp";

            int numChannels = 3;
            unsigned char data[width * height * numChannels];

            int arrayIndex = 0;
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {

                    /// Interpolatiion tests
                    /*
                    glm::vec3 startColor = glm::vec3(60,136,199);
                    glm::vec3 endColor = glm::vec3(239,238,236);
                    float x = rgb[i][j] / 255.0f;
                    float r = ((endColor.x - startColor.x) * x) + startColor.x;
                    float g = ((endColor.y - startColor.y) * x) + startColor.y;
                    float b = ((endColor.z - startColor.z) * x) + startColor.z;
                    */

                    /// Interpolating Cloud Textures [C]
                    /*glm::vec3 startColor = glm::vec3(60,136,199);
                    glm::vec3 endColor = glm::vec3(239,238,236);
                    float x = rgb[i][j] / 255.0f;
                    float r = ((endColor.x - startColor.x) * x) + startColor.x;
                    float g = ((endColor.y - startColor.y) * x) + startColor.y;
                    float b = ((endColor.z - startColor.z) * x) + startColor.z;*/


                    /// Interpolating Marble Textures [M]
                    /*glm::vec3 startColor = glm::vec3(121,121,121);
                    glm::vec3 startColorSecondary = glm::vec3(221,221,221);
                    glm::vec3 endColor = glm::vec3(255,255,255);

                    float r, b, g;
                    float x = rgb[i][j] / 255.0f;

                    // Thin out lines
                    if (x < 0.1) {
                        r = ((endColor.x - startColor.x) * x) + startColor.x;
                        g = ((endColor.y - startColor.y) * x) + startColor.y;
                        b = ((endColor.z - startColor.z) * x) + startColor.z;
                    } else {
                        r = ((endColor.x - startColorSecondary.x) * x) + startColorSecondary.x;
                        g = ((endColor.y - startColorSecondary.y) * x) + startColorSecondary.y;
                        b = ((endColor.z - startColorSecondary.z) * x) + startColorSecondary.z;
                    }*/

                    /// Interpolating Water Textures [BL]
                    /*
                    glm::vec3 startColor = glm::vec3(4, 78, 74);
                    glm::vec3 endColor = glm::vec3(228, 222, 201);
                    float x = rgb[i][j] / 255.0f;
                    float r = ((endColor.x - startColor.x) * x) + startColor.x;
                    float g = ((endColor.y - startColor.y) * x) + startColor.y;
                    float b = ((endColor.z - startColor.z) * x) + startColor.z;
                    */

                    /// Interpolating Darker Water Textures [DBL]
                    /*glm::vec3 startColor = glm::vec3(15, 32, 39);
                    glm::vec3 endColor = glm::vec3(44, 83, 100);
                    float x = rgb[i][j] / 255.0f;
                    float r = ((endColor.x - startColor.x) * x) + startColor.x;
                    float g = ((endColor.y - startColor.y) * x) + startColor.y;
                    float b = ((endColor.z - startColor.z) * x) + startColor.z;*/

                    /// Interpolating Basketball [BSK]
                    /*glm::vec3 startColor = glm::vec3(117, 78, 29);
                    glm::vec3 endColor = glm::vec3(64, 41, 12);
                    float x = rgb[i][j] / 255.0f;
                    float r = ((endColor.x - startColor.x) * x) + startColor.x;
                    float g = ((endColor.y - startColor.y) * x) + startColor.y;
                    float b = ((endColor.z - startColor.z) * x) + startColor.z;*/


                    /// Interpolating Rock [RK]
                    /*glm::vec3 startColor = glm::vec3(46.0f, 40.0f, 34.0f);
                    glm::vec3 endColor = glm::vec3(233.0f, 231.0f, 229.0f);
                    float x = rgb[i][j] / 255.0f;
                    float r = ((endColor.x - startColor.x) * x) + startColor.x;
                    float g = ((endColor.y - startColor.y) * x) + startColor.y;
                    float b = ((endColor.z - startColor.z) * x) + startColor.z;*/

                    /// Interpolating Brown [BR]
                    glm::vec3 startColor = glm::vec3(78,53,4);
                    glm::vec3 endColor = glm::vec3(208,186,144);
                    float x = rgb[i][j] / 255.0f;
                    float r = ((endColor.x - startColor.x) * x) + startColor.x;
                    float g = ((endColor.y - startColor.y) * x) + startColor.y;
                    float b = ((endColor.z - startColor.z) * x) + startColor.z;

                    /// Quintic Smoothing with Blues/Purples [BP]
                    /*
                    float intensityR = 1.0f;
                    float intensityG = 1.0f;
                    float intensityB = 1.0f;
                    float x = rgb[i][j] / 255.0f;
                    float r = (50.0f - (470.0833f * x) + (5059.375f * pow(x, 2)) -
                              (11723.96f * pow(x, 3)) + (11015.62f *  pow(x, 4)) -
                              (3723.958f * pow(x, 5))) * intensityR;
                    float g = (126.0f - (758.3333f * x) + (3635.417f * pow(x, 2)) -
                              (6838.542f * pow(x, 3)) + (5989.583f * pow(x, 4)) -
                              (1953.125f * pow(x, 5))) * intensityG;
                    float b = (178.0f - (160.5f * x) + (1756.25f * pow(x, 2)) -
                              (4979.167f * pow(x, 3)) + (5156.25f * pow(x, 4)) -
                              (1770.833f * pow(x, 5))) * intensityB;
                    */

                    /// Tiny Color Map Implementations
                    /*float x = rgb[i][j] / 255.0f;
                    //const tinycolormap::Color color = tinycolormap::GetColor(x, tinycolormap::ColormapType::Magma);         // Black-Purple-Pink-Orange-Yellow
                    //const tinycolormap::Color color = tinycolormap::GetColor(x, tinycolormap::ColormapType::Github);     // White-Green
                    //const tinycolormap::Color color = tinycolormap::GetColor(x, tinycolormap::ColormapType::Viridis);     // Purple-Blue-Green-Yellow
                    //const tinycolormap::Color color = tinycolormap::GetColor(x, tinycolormap::ColormapType::Cividis);     // Blue-Brown-Yellow
                    //const tinycolormap::Color color = tinycolormap::GetColor(x, tinycolormap::ColormapType::Heat);        // Blue-Teal-Green-Yellow-Orange-Red
                    const tinycolormap::Color color = tinycolormap::GetColor(x, tinycolormap::ColormapType::Hot);         // Black-Burgundy-Red-Orange-Yellow
                    //const tinycolormap::Color color = tinycolormap::GetColor(x, tinycolormap::ColormapType::Gray);         // Gray
                    float r = (float)color.r() * 255.0f;
                    float g = (float)color.g() * 255.0f;
                    float b = (float)color.b() * 255.0f;*/

                    //printf("\nRGB[%f]: %f, %f, %f", x, r, g, b);

                    data[arrayIndex++] = r;
                    data[arrayIndex++] = g;
                    data[arrayIndex++] = b;
                }
            }

            printf("\nAttempting to write coloured noise as BMP.\n");

            stbi_write_bmp(filename.c_str(), width, height, 3, data);
            printf("    BMP written: %s\n", filename.c_str());

            stbi_write_bmp(filenameTemp.c_str(), width, height, 3, data);
            printf("    BMP written: %s\n", filenameTemp.c_str());
            printf("Successfully wrote noise as BMP.\n");
        }
    }
}


/*
 * Output SVG header.
 */
void ImageOutput::headerSVG(std::ofstream& outfile, int width, int height, std::string file) {

    std::string svgHeaderPart1="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
		"<!-- Created with CurveBenchmark -->\n"
		"<svg\n"
		"    xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
		"    xmlns:cc=\"http://creativecommons.org/ns#\"\n"
		"    xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
		"    xmlns:svg=\"http://www.w3.org/2000/svg\"\n"
		"    xmlns=\"http://www.w3.org/2000/svg\"\n"
		"    xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
		"    xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n"
		"    width=\"";
	std::string svgHeaderPart2="\"\n"
		"    height=\"";
	std::string svgHeaderPart3="\"\n"
		"    id=\"svg2\"\n"
		"    version=\"1.1\"\n"
//		"    inkscape:version=\"0.48.1 r9760\"\n";
		"    sodipodi:docname=\"";
	std::string svgHeaderPart4 = "\">\n"
		"<defs\n"
		"    id=\"defs4\" />\n"
		"<metadata\n"
		"    id=\"metadata7\">\n"
		"    <rdf:RDF>\n"
		"        <cc:Work\n"
		"            rdf:about=\"\">\n"
		"            <dc:format>image/svg+xml</dc:format>\n"
		"            <dc:type\n"
		"                rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\" />\n"
		"            <dc:title></dc:title>\n"
		"        </cc:Work>\n"
		"    </rdf:RDF>\n"
		"</metadata>\n"
		"<g\n"
		"    inkscape:label=\"Layer 1\"\n"
		"    inkscape:groupmode=\"layer\"\n"
		"    id=\"layer1\">\n";

	outfile << svgHeaderPart1 << width << svgHeaderPart2 << height << svgHeaderPart3 << file << svgHeaderPart4 << std::endl;
}

/*
 * Output SVG footer.
 */
void ImageOutput::footerSVG(std::ofstream& outfile) {
    std::string svgFooter = "    </g>\n"
                       "</svg>";

    outfile << svgFooter << std::endl;
}

/*
 * Saves image as SVG file, if enabled in driver.
 *
 * Parameters:
 *      points: Vector of point structs
 *      writeBMP: 0 being do no create BMP and 1 being create BMP
 *      width: pixels in x-dimension
 *      height: pixels in y-dimension
 */
void ImageOutput::saveSVG(std::vector<Noise::Point> points, int writeSVG, int width, int height, std::string file) {

    // TODO: Add coloured output
    // TODO: Add support for analysis and Fourier save

    if (writeSVG == 1) {

        std::string filename = "../Output/Noise/" + file + ".svg";
        printf("\nAttempting to write noise as SVG.\n");

        std::ofstream outfile;
        outfile.open(filename);

        int outputWidth = 1200, outputHeight = 1200, padding = 100;
        float radius = 1.0f;

        headerSVG(outfile, outputWidth, outputHeight, file);

        for (int i = 0; i < points.size(); i++) {
            int temp = floor(255.0f * points[i].colour);

            // FIXME: Rendering flipped x & y
            //outfile << "    <circle cx=\"" << (padding + points[i].y) / 2.0f << "\" cy=\"" << (padding + points[i].x) / 2.0f << "\" r=\"" << radius << "\" fill=\"rgb(" << temp << ", " << temp << ", " << temp << ")\" id=\"circle" << i << "\"/>\n";
            outfile << "    <rect x=\"" << (padding + points[i].y) - 0.5 << "\" y=\"" << (padding + points[i].x) - 0.5 << "\" width=\"1.25\" height=\"1.25\" stoke=\"rgb(" << temp << ", " << temp << ", " << temp << ")\" fill=\"rgb(" << temp << ", " << temp << ", " << temp << ")\" id=\"rect" << i << "\"/>\n";
        }

        footerSVG(outfile);
        outfile.close();

        printf("    SVG written: %s\n", filename.c_str());
        printf("Successfully wrote noise as SVG.\n");
    }
}
