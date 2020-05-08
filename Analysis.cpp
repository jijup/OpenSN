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

        printf("Starting amplitude analysis.\n");

        // Create title of output
        std::string title = "../Analysis/Amplitude/AmplitudeAnalysis_Pair" + std::to_string(pairingFunction) + "_Noise" + std::to_string(noiseType)
                            + "_W" + std::to_string(width) + "_H" + std::to_string(height) + ".bmp";

        std::vector<float> test_data;
        for (int i = 0; i < points.size(); i++) {
            test_data.push_back(points[i].colour);
        }

        plt::figure_size(1000, 1000);
        plt::hist(test_data, 1000);
        plt::save(title);

        printf("    Amplitude analysis written: %s\n", title.c_str());
        printf("Successfully completed amplitude analysis.\n");

        /*
        // PREVIOUS AMPLITUDE ANALYSIS - SAVE TO CSV
        // Create title of output
        std::string title = "../Analysis/Amplitude/AmplitudeAnalysis_Pair" + std::to_string(pairingFunction) + "_Noise" + std::to_string(noiseType)
             + "_W" + std::to_string(width) + "_H" + std::to_string(height) + ".csv";

        // Convert title to character array
        int titleLength = title.length();
        char filename[titleLength + 1];
        strcpy(filename, title.c_str());
        std::ofstream outFile;

        outFile.open(filename, std::ios::out);

        outFile << "GaussianAmplitude\n";

        // Loop through points and write to CSV
        for (int i = 0; i < points.size(); i++) {
            outFile << points[i].colour << "\n";
        }

        outFile.close();
        printf("    Amplitude analysis written: %s\n", title.c_str());
        printf("Successfully completed amplitude analysis.\n");
         */
    }

    // Fourier analysis
    if (fourierAnalysis == 1) {

        printf("Starting Fourier analysis.\n");

        // Read noise file via OpenCV imread (properly formats into cv::Mat object)
        const char* filename = "../Output/temp/noise_output.bmp";
        cv::Mat I = imread( cv::samples::findFile(filename), cv::IMREAD_GRAYSCALE);
        if(I.empty()) {
            std::cout << "[Analysis.cpp] Error: reading image from" << filename << std::endl;
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

        // Loop through points and assign noise values to RGB array
        unsigned char rgb[magI.cols][magI.rows];
        for (int i = 0 ; i < magI.cols; ++i) {
            for (int j = 0; j < magI.rows; ++j) {
                colourByte = uint8_t(magI.at<float>(i, j) * 0xff);
                rgb[i][j] = colourByte;
            }
        }

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
        std::string title = "../Analysis/Fourier/FourierAnalysis_Pair" + std::to_string(pairingFunction) + "_Noise" + std::to_string(noiseType)
                            + "_W" + std::to_string(width) + "_H" + std::to_string(height) + ".bmp";

        stbi_write_bmp(title.c_str(), width, height, 1, data);

        printf("    Fourier analysis written: %s\n", title.c_str());
        printf("Successfully completed Fourier analysis.\n");
    }
}