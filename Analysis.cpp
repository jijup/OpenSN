/**
 * Analysis.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementations of various analysis techniques. Usage of OpenCV documentation for Fourier analysis. See reference.
 *
 * Reference: (https://docs.opencv.org/3.4/d8/d01/tutorial_discrete_fourier_transform.html).
 */

#include "Analysis.h"

Analysis::Analysis() {}

Analysis::~Analysis() {}

void Analysis::runAnalysis(std::vector<Noise::Point> points, int pairingFunction, int noiseType, int width, int height, int ampAnalysis, int fourierAnalysis) {

    // Amplitude analysis
    if (ampAnalysis == 1) {

        printf("    Starting amplitude analysis.\n");

        // Create title of output
        std::string title = "../Analysis/Amplitude/AmplitudeAnalysis_Pair" + std::to_string(pairingFunction) + "_Noise" + std::to_string(noiseType)
                            + "_W" + std::to_string(width) + "_H" + std::to_string(height) + ".bmp";

        // Format as vector
        std::vector<float> test_data;
        for (int i = 0; i < points.size(); i++) {
            test_data.push_back(points[i].colour);
        }

        /// Save as BMP
        plt::figure_size(500, 500);
        plt::xlim(0.0, 1.0);
        plt::hist(test_data, 1000);
        //plt::axis("off");
        plt::save(title);

        printf("        Amplitude analysis written to BMP: %s\n", title.c_str());

        /// Save as SVG
        /*const char* filename = title.c_str();
        cv::Mat I = imread( cv::samples::findFile(filename), cv::IMREAD_GRAYSCALE);
        if(I.empty()) {
            std::cout << "    [Analysis.cpp] Error: reading image from" << filename << std::endl;
        }

        // Expand input image to optimal size
        cv::Mat padded;
        int m = cv::getOptimalDFTSize(I.rows);
        int n = cv::getOptimalDFTSize(I.cols);

        // Add zero values on border
        copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
        cv::Mat planes[] = {
                cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)
        };
        cv::Mat complexI;

        // Add to the expanded another plane with zeros
        merge(planes, 2, complexI);
        cv::Mat magI = planes[0];
        normalize(magI, magI, 0, 1, cv::NORM_MINMAX);

        title = "../Analysis/Amplitude/AmplitudeAnalysis_Pair" + std::to_string(pairingFunction) + "_Noise" + std::to_string(noiseType)
                + "_W" + std::to_string(width) + "_H" + std::to_string(height) + ".svg";
        int outputWidth = 1200, outputHeight = 1200, padding = 100;

        std::ofstream outfile;
        outfile.open(title);

        headerSVG(outfile, outputWidth, outputHeight, "Fourier Analysis");

        for (int i = 0 ; i < magI.cols; ++i) {
            for (int j = 0; j < magI.rows; ++j) {
                int temp = floor(255.0f * magI.at<float>(i, j));
                //outfile << "    <circle cx=\"" << (padding + j) / 2.0f << "\" cy=\"" << (padding + i) / 2.0f << "\" r=\"" << 0.75f << "\" fill=\"rgb(" << temp << ", " << temp << ", " << temp << ")\" id=\"circle" << i*width+j << "\"/>\n";
                outfile << "    <rect x=\"" << (padding + j) - 0.5 << "\" y=\"" << (padding + i) - 0.5 << "\" width=\"1.25\" height=\"1.25\" stoke=\"rgb(" << temp << ", " << temp << ", " << temp << ")\" fill=\"rgb(" << temp << ", " << temp << ", " << temp << ")\" id=\"rect" << i*width+j << "\"/>\n";
            }
        }

        // Draw X-axis line
        outfile << "    <line x1=\"50\" y1=\"250\" x2=\"250\" y2=\"250\" stroke=\"black\" />";

        // Draw tickmarks
        outfile << "    <line x1=\"50\" y1=\"250\" x2=\"50\" y2=\"255\" stroke=\"black\" />";
        outfile << "    <line x1=\"100\" y1=\"250\" x2=\"100\" y2=\"255\" stroke=\"black\" />";
        outfile << "    <line x1=\"150\" y1=\"250\" x2=\"150\" y2=\"255\" stroke=\"black\" />";
        outfile << "    <line x1=\"200\" y1=\"250\" x2=\"200\" y2=\"255\" stroke=\"black\" />";
        outfile << "    <line x1=\"250\" y1=\"250\" x2=\"250\" y2=\"255\" stroke=\"black\" />";

        // Tickmark labels
        outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"50\" y=\"265\" font-size=\"10px\">0.0</text>";
        outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"100\" y=\"265\" font-size=\"10px\">0.25</text>";
        outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"150\" y=\"265\" font-size=\"10px\">0.5</text>";
        outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"200\" y=\"265\" font-size=\"10px\">0.75</text>";
        outfile << "<text font-family=\"Times, serif\" text-anchor=\"middle\" alignment-baseline=\"middle\" x=\"250\" y=\"265\" font-size=\"10px\">1.0</text>";

        footerSVG(outfile);
        outfile.close();

        printf("        Amplitude analysis written to SVG: %s\n", title.c_str());
        printf("    Successfully completed amplitude analysis.\n");*/

    }

    // Fourier analysis
    if (fourierAnalysis == 1) {

        printf("    Starting Fourier analysis.\n");

        /// Fourier transform
        // Read noise file via OpenCV imread (properly formats into cv::Mat object)
        const char* filename = "../Output/temp/noise_output.bmp";
        cv::Mat I = imread( cv::samples::findFile(filename), cv::IMREAD_GRAYSCALE);
        if(I.empty()) {
            std::cout << "    [Analysis.cpp] Error: reading image from" << filename << std::endl;
        }

        // Expand input image to optimal size
        cv::Mat padded;
        int m = cv::getOptimalDFTSize(I.rows);
        int n = cv::getOptimalDFTSize(I.cols);

        // Add zero values on border
        copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
        cv::Mat planes[] = {
                cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)
        };
        cv::Mat complexI;

        // Add to the expanded another plane with zeros
        merge(planes, 2, complexI);

        // Compute Fourier transform
        dft(complexI, complexI);

        // Compute the magnitude and switch to logarithmic scale            // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
        split(complexI, planes);                                            // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
        magnitude(planes[0], planes[1], planes[0]);      // planes[0] = magnitude
        cv::Mat magI = planes[0];
        magI += cv::Scalar::all(1);                                    // switch to logarithmic scale
        log(magI, magI);

        // Crop the spectrum (if it has an odd number of rows or columns)
        magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

        // Rearrange the quadrants of Fourier image so that the origin is at the image center
        int cx = magI.cols/2;
        int cy = magI.rows/2;
        cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));          // Top-Left - Create a ROI per quadrant
        cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));              // Top-Right
        cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));              // Bottom-Left
        cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy));                  // Bottom-Right

        // Swap quadrants (Top-Left with Bottom-Right)
        cv::Mat tmp;
        q0.copyTo(tmp);
        q3.copyTo(q0);
        tmp.copyTo(q3);

        // Swap quadrant (Top-Right with Bottom-Left)
        q1.copyTo(tmp);
        q2.copyTo(q1);
        tmp.copyTo(q2);

        // Transform the matrix with float values into a
        normalize(magI, magI, 0, 1, cv::NORM_MINMAX);

        // Viewable image form via OpenCV (float between values 0 and 1).
        //imshow("Spectrum Magnitude", magI);
        //cv::waitKey();

        // Start conversion for output
        unsigned char *input = (unsigned char*)(magI.data);
        uint8_t colourByte;

        /// Save as SVG
        std::string title = "../Analysis/Fourier/FourierAnalysis_Pair" + std::to_string(pairingFunction) + "_Noise" + std::to_string(noiseType)
                + "_W" + std::to_string(width) + "_H" + std::to_string(height) + ".svg";
        /*int outputWidth = 1200, outputHeight = 1200, padding = 100;

        std::ofstream outfile;
        outfile.open(title);

        headerSVG(outfile, outputWidth, outputHeight, "Fourier Analysis");*/

        // Loop through points and assign noise values to RGB array
        unsigned char rgb[magI.cols][magI.rows];
        for (int i = 0 ; i < magI.cols; ++i) {
            for (int j = 0; j < magI.rows; ++j) {
                int temp = floor(255 * magI.at<float>(i, j));
                //outfile << "    <rect x=\"" << (padding + i) - 0.5 << "\" y=\"" << (padding + j) - 0.5 << "\" width=\"1.25\" height=\"1.25\" stoke=\"rgb(" << temp << ", " << temp << ", " << temp << ")\" fill=\"rgb(" << temp << ", " << temp << ", " << temp << ")\" id=\"rect" << i*width+j << "\"/>\n";

                colourByte = uint8_t(magI.at<float>(i, j) * 0xff);
                rgb[i][j] = colourByte;
            }
        }

        /*footerSVG(outfile);
        outfile.close();
        printf("        Fourier analysis written as SVG: %s\n", title.c_str());*/

        /// Save as BMP
        // Loop through previously generated array and place into sequential char array for output to BMP
        int numChannels = 3;
        unsigned char data[width * height * numChannels];
        int arrayIndex = 0;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                data[arrayIndex++] = rgb[i][j];
            }
        }

        // Create title of output
        title = "../Analysis/Fourier/FourierAnalysis_Pair" + std::to_string(pairingFunction) + "_Noise" + std::to_string(noiseType)
                            + "_W" + std::to_string(width) + "_H" + std::to_string(height) + ".bmp";

        // Save as BMP
        stbi_write_bmp(title.c_str(), width, height, 1, data);

        printf("        Fourier analysis written as BMP: %s\n", title.c_str());
        printf("    Successfully completed Fourier analysis.\n");

        // Restore original image
        /*cv::Mat inverseTransform;
        cv::dft(complexI, inverseTransform, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT);
        normalize(inverseTransform, inverseTransform, 0, 1, cv::NORM_MINMAX);
        imshow("Reconstructed", inverseTransform);
        cv::waitKey();*/
    }
}

/*
 * Output SVG header.
 */
void Analysis::headerSVG(std::ofstream& outfile, int width, int height, std::string file) {

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
                               //		"    inkscape:version=\"0.48.1 r9760\"\n"
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
void Analysis::footerSVG(std::ofstream& outfile) {
    std::string svgFooter = "    </g>\n"
                            "</svg>";

    outfile << svgFooter << std::endl;
}