/**
 * BetterGradient.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A Better Gradient noise implementation.
 *
 * Implementation heavily based on "Better Gradient Noise" by Kensler, Knoll & Shirly
 *
 * Reference: https://sci.utah.edu/publications/SCITechReports/UUSCI-2008-001.pdf
 */

#include "BetterGradient.h"

BetterGradient::BetterGradient() {
    srand(time(NULL));

    permutationTableX = new int[256];
    permutationTableY = new int[256];
    permutationTableZ = new int[256];
    gradientX = new float[256];
    gradientY = new float[256];
    gradientZ = new float[256];

    for (int i = 0; i < 256; ++i) {
        permutationTableX[i] = i;
        permutationTableY[i] = i;
        permutationTableZ[i] = i;


        gradientX[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
        gradientY[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
        gradientZ[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
    }

    int swapIndex = 0;
    int temp = 0;
    for (int i = 0; i < 256; i++) {
        swapIndex = rand() & 255;
        temp = permutationTableX[i];
        permutationTableX[i] = permutationTableX[swapIndex];
        permutationTableX[swapIndex] = temp;

        swapIndex = rand() & 255;
        temp = permutationTableY[i];
        permutationTableY[i] = permutationTableY[swapIndex];
        permutationTableY[swapIndex] = temp;

        swapIndex = rand() & 255;
        temp = permutationTableZ[i];
        permutationTableZ[i] = permutationTableZ[swapIndex];
        permutationTableZ[swapIndex] = temp;
    }
}

BetterGradient::~BetterGradient() {
    delete permutationTableX;
    delete permutationTableY;
    delete permutationTableZ;
    delete gradientX;
    delete gradientY;
    delete gradientZ;
}

float BetterGradient::noise(float xCoord, float yCoord, float zCoord) {


    int gradientX0 = int(floor(xCoord));
    int gradientY0 = int(floor(yCoord));
    int gradientZ0 = int(floor(zCoord));

    glm::vec3 X = glm::vec3(xCoord, yCoord, zCoord);
    glm::vec3 I = glm::vec3(gradientX0, gradientY0, gradientZ0);
    glm::vec3 F = X - I;

    glm::vec3 N = glm::vec3(0.0f, 0.0f, 0.0f);
    float _v = 0.0f;


    int dimensionFlag = 1;
    if (dimensionFlag == 0) {
            for (int j = -1; j <= 2; j++) {
                for (int i = -1; i <= 2; i++) {

                    glm::vec3 D = F - glm::vec3(i, j, 1);

                    float o = glm::dot(D, N);
                    glm::vec3 A = D - o*N;
                    float d = glm::dot(A, A);

                    o = 1 - abs(o);

                    if (d < 4 && o > 0) {
                        //int h = (permutationTableX[(gradientX0 + i) & 255]) ^ (permutationTableY[(gradientY0 + j) & 255]) ^ (permutationTableZ[(gradientZ0 + k) & 255]);
                        int h = (permutationTableX[(gradientX0 + i) & 255]) ^ (permutationTableY[(gradientY0 + j) & 255]);
                        float t = 1.0f - d / 4.0f;

                        glm::vec3 G_h = glm::vec3(gradientX[h], gradientY[h], 1);

                        float tempResult = (glm::dot(A, G_h)) * (4.0f * pow(t, 5.0f) - 3.0f * pow(t, 4.0f)) * (3.0f * pow(o, 2.0f) - 2.0f * pow(o, 3.0f));
                        _v = _v + tempResult;
                    }
                }
            }

        return _v;
    } else {
        for (int k = -1; k <= 2; k++) {
            for (int j = -1; j <= 2; j++) {
                for (int i = -1; i <= 2; i++) {

                    glm::vec3 D = F - glm::vec3(i, j, k);

                    float o = glm::dot(D, N);
                    glm::vec3 A = D - o*N;
                    float d = glm::dot(A, A);

                    o = 1 - abs(o);

                    if (d < 4 && o > 0) {
                        int h = (permutationTableX[(gradientX0 + i) & 255]) ^ (permutationTableY[(gradientY0 + j) & 255]) ^ (permutationTableZ[(gradientZ0 + k) & 255]);
                        float t = 1.0f - d / 4.0f;

                        glm::vec3 G_h = glm::vec3(gradientX[h], gradientY[h], gradientZ[h]);

                        float tempResult = (glm::dot(A, G_h)) * (4.0f * pow(t, 5.0f) - 3.0f * pow(t, 4.0f)) * (3.0f * pow(o, 2.0f) - 2.0f * pow(o, 3.0f));
                        _v = _v + tempResult;
                    }
                }
            }
        }

        return _v;
    }

}
