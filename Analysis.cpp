/*
 * Analysis.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementations for various analysis techniques.
 */

#include "Analysis.h"
#include <string>

Analysis::Analysis() {}

Analysis::~Analysis() {}

void Analysis::runAnalysis(std::vector<Noise::Point> points, int pairingFunction, int noiseType, int textureType, int width, int height, int ampAnalysis, int fournierAnalysis) {

    if (ampAnalysis == 1) {

        // Create title of output
        std::string title = "../Analysis/AmplitudeAnalysis_Pair" + std::to_string(pairingFunction) + "_Noise" + std::to_string(noiseType)
                + "_Tex" + std::to_string(textureType) + "_W" + std::to_string(width) + "_H" + std::to_string(height);

        // Convert title to character array
        int titleLength = title.length();
        char filename[titleLength + 1];
        strcpy(filename, title.c_str());
        //char filename[] = "../Analysis/amplitude_out.csv";
        std::ofstream outFile;

        //outFile.open(filename, std::ios::out | std::ios::app);
        outFile.open(filename, std::ios::out);

        outFile << "GaussianAmplitude\n";

        // Loop through points and write to CSV
        for (int i = 0; i < points.size(); i++) {
            outFile << points[i].colour << "\n";
        }

        outFile.close();
        printf("Amplitude analysis written to CSV.\n");
    }

    if (fournierAnalysis == 1) {
        // Create title of output
        std::string title = "../Analysis/FournierAnalysis_Pair" + std::to_string(pairingFunction) + "_Noise" + std::to_string(noiseType)
                            + "_Tex" + std::to_string(textureType) + "_W" + std::to_string(width) + "_H" + std::to_string(height);

        // Convert title to character array
        int titleLength = title.length();
        char filename[titleLength + 1];
        strcpy(filename, title.c_str());
        //char filename[] = "../Analysis/amplitude_out.csv";
        std::ofstream outFile;

        //outFile.open(filename, std::ios::out | std::ios::app);
        outFile.open(filename, std::ios::out);

        outFile << "GaussianAmplitude\n";

        // Loop through points and write to CSV
        for (int i = 0; i < points.size(); i++) {
            outFile << points[i].colour << "\n";
        }

        outFile.close();
        printf("Fournier analysis written to CSV.\n");
    }

}