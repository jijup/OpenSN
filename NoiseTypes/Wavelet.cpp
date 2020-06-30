/**
 * Wavelet.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A Wavelet noise implementation.
 *
 * Implementation heavily based on "Wavelet Noise" by Cook & DeRose.
 *
 * Reference: https://graphics.pixar.com/library/WaveletNoise/paper.pdf
 */

#include "Wavelet.h"

#define ARAD 16

Wavelet::Wavelet() {
    srand(time(NULL));

    int n = 10;
    int olap = 0;
    generateNoiseTile(n, olap);

}

Wavelet::~Wavelet() {}

int Wavelet::mod(int x, int n) {
    int m = x % n; return (m < 0) ? m + n : m;
}

void Wavelet::downsample (float *from, float *to, int n, int stride ) {
    float *a, aCoeffs[2*ARAD] = {
            0.000334,-0.001528, 0.000410, 0.003545,-0.000938,-0.008233, 0.002172, 0.019120,
            -0.005040,-0.044412, 0.011655, 0.103311,-0.025936,-0.243780, 0.033979, 0.655340,
            0.655340, 0.033979,-0.243780,-0.025936, 0.103311, 0.011655,-0.044412,-0.005040,
            0.019120, 0.002172,-0.008233,-0.000938, 0.003546, 0.000410,-0.001528, 0.000334};
    a = &aCoeffs[ARAD];
    for (int i=0; i<n/2; i++) {
        to[i*stride] = 0;
        for (int k=2*i-ARAD; k<=2*i+ARAD; k++)
            to[i*stride] += a[k-2*i] * from[mod(k,n)*stride];
    }
}
void Wavelet::upsample( float *from, float *to, int n, int stride) {
    float *p, pCoeffs[4] = { 0.25, 0.75, 0.75, 0.25 };
    p = &pCoeffs[2];
    for (int i=0; i<n; i++) {
        to[i*stride] = 0;
        for (int k=i/2; k<=i/2+1; k++)
            to[i*stride] += p[i-2*k] * from[mod(k,n/2)*stride];
    }
}
void Wavelet::generateNoiseTile( int n, int olap) {
    if (n%2) n++; /* tile size must be even */
    int ix, iy, iz, i, sz=n*n*n*sizeof(float);
    float *temp1=(float *)malloc(sz),*temp2=(float *)malloc(sz),*noise=(float *)malloc(sz);
/* Step 1. Fill the tile with random numbers in the range -1 to 1. */
    //for (i=0; i<n*n*n; i++) noise[i] = gaussianNoise();
    for (i=0; i<n*n*n; i++) noise[i] = (float(rand()) / (RAND_MAX/2)) - 1.0f;
/* Steps 2 and 3. Downsample and upsample the tile */
    for (iy=0; iy<n; iy++) for (iz=0; iz<n; iz++) { /* each x row */
            i = iy*n + iz*n*n; downsample( &noise[i], &temp1[i], n, 1 );
            upsample( &temp1[i], &temp2[i], n, 1 );
        }
    for (ix=0; ix<n; ix++) for (iz=0; iz<n; iz++) { /* each y row */
            i = ix + iz*n*n; downsample( &temp2[i], &temp1[i], n, n );
            upsample( &temp1[i], &temp2[i], n, n );
        }
    for (ix=0; ix<n; ix++) for (iy=0; iy<n; iy++) { /* each z row */
            i = ix + iy*n; downsample( &temp2[i], &temp1[i], n, n*n );
            upsample( &temp1[i], &temp2[i], n, n*n );
        }
/* Step 4. Subtract out the coarse-scale contribution */
    for (i=0; i<n*n*n; i++) {noise[i]-=temp2[i];}
/* Avoid even/odd variance difference by adding odd-offset version of noise to itself.*/
    int offset=n/2; if (offset%2==0) offset++;
    for (i=0,ix=0; ix<n; ix++) for (iy=0; iy<n; iy++) for (iz=0; iz<n; iz++)
                temp1[i++] = noise[ mod(ix+offset,n) + mod(iy+offset,n)*n + mod(iz+offset,n)*n*n ];
    for (i=0; i<n*n*n; i++) {noise[i]+=temp1[i];}
    noiseTileData=noise; noiseTileSize=n; free(temp1); free(temp2);
}

float Wavelet::noise(float xCoord, float yCoord, float zCoord) {

    float p[3] = {xCoord, yCoord, zCoord};
    // f, c = filter, noise coeff indices
    int i, f[3], c[3], mid[3], n = noiseTileSize;
    float w[3][3], t, result = 0;

    // Evaluate quadratic B-spline basis functions
    for (i = 0; i < 3; i++) {
        mid[i] = ceil(p[i] - 0.5); t = mid[i] - (p[i] - 0.5);
        w[i][0] = t*t / 2; w[i][2] = (1 - t) * (1 - t) / 2; w[i][1] = 1 - w[i][0] - w[i][2];
    }

    // Evaluate noise by weighting noise coefficients by basis function values
    for(f[2] = -1; f[2] <= 1; f[2]++) {
        for(f[1] = -1; f[1] <= 1; f[1]++) {
            for (f[0] = -1; f[0] <= 1; f[0]++) {
                float weight = 1;
                for (i = 0; i < 3; i++) {
                    c[i] = mod(mid[i] + f[i], n);
                    weight *= w[i][f[i] + 1];
                }

                result += weight * noiseTileData[c[2] * n * n + c[1] * n + c[0]];
            }
        }
    }

    return result;
}
