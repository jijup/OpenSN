/**
 * Phasor.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * A Phasor noise implementation.
 *
 * Implementation heavily based on "Procedural Phasor Noise" by Tricard, Efremov, Zanni, Neyret, Martinez, Lefebvre.
 *
 * Reference: https://dl.acm.org/doi/pdf/10.1145/3306346.3322990?download=true
 */

#include "Phasor.h"

Phasor::Phasor() {
    srand(time(NULL));

    init_noise();

}

Phasor::~Phasor() {}

glm::vec2 Phasor::phasor(glm::vec2 x, float f, float b, float o, float phi) {

    float a = exp(-M_PI * (b * b) * ((x.x * x.x) + (x.y * x.y)));
    float s = sin (2.0* M_PI * f  * (x.x*cos(o) + x.y*sin(o))+phi);
    float c = cos (2.0* M_PI * f  * (x.x*cos(o) + x.y*sin(o))+phi);
    return glm::vec2(a*c,a*s);
}

int Phasor::morton(int x, int y) {
    int z = 0;
    for (int i = 0 ; i < 32* 4 ; i++) {
        z |= ((x & (1 << i)) << i) | ((y & (1 << i)) << (i + 1));
    }
    return z;
}


void Phasor::init_noise() {
    _kr = sqrt(-log(0.05) / M_PI) / _b;
}


glm::vec2 Phasor::cell(glm::ivec2 ij, glm::vec2 uv, float f, float b) {
    int s= morton(ij.x,ij.y) + 333;
    s = s==0? 1: s +_seed;
    seed(s);
    int impulse  =0;
    int nImpulse = _impPerKernel;
    float  cellsz = 2.0 * _kr;
    glm::vec2 noise = glm::vec2(0.0);
    while (impulse <= nImpulse){
        glm::vec2 impulse_centre = glm::vec2(uni_0_1(),uni_0_1());
        glm::vec2 d = (uv - impulse_centre) *cellsz;
        float rp = uni(0.0,2.0*M_PI);
        glm::vec2 trueUv = ((glm::vec2(ij) + impulse_centre) *cellsz) *  (float)height / (float)width;
        trueUv.y = -trueUv.y;
        float o = (trueUv.x) * 2.0* M_PI;
        //float o = 2.0* M_PI;
        noise = noise + phasor(d, f, b ,o,rp );
        impulse++;
    }
    return noise;
}

glm::vec2 Phasor::eval_noise(glm::vec2 uv, float f, float b) {
    float cellsz = 2.0 *_kr;
    glm::vec2 _ij = uv / cellsz;
    glm::ivec2  ij = glm::ivec2(_ij);
    glm::vec2  fij = _ij - glm::vec2(ij);
    glm::vec2 noise = glm::vec2(0.0);
    for (int j = -2; j <= 2; j++) {
        for (int i = -2; i <= 2; i++) {
            glm::ivec2 nij = glm::ivec2(i, j);
            noise = noise + cell(ij + nij , fij - glm::vec2(nij),f,b);
        }
    }
    return noise;
}

float Phasor::PWM(float x, float r) {

    float mod = x - (floor(x / 2.0f*M_PI) * 2.0f*M_PI);

    //return mod(x,2.0*M_PI)> 2.0*M_PI *r ? 1.0 : 0.0;
    return mod> 2.0*M_PI *r ? 1.0 : 0.0;
}

float Phasor::square(float x) {
    return PWM(x,0.5);
}

float Phasor::sawTooth(float x) {

    float mod = x - (floor(x / 2.0f*M_PI) * 2.0f*M_PI);

    //return mod(x,2.0*M_PI)/(2.0*M_PI);
    return mod/(2.0*M_PI);
}


float Phasor::noise(float xCoord, float yCoord, float zCoord) {

    uv = glm::vec2(xCoord, yCoord);
    uv.y=-uv.y;
    //init_noise();
    float o = 0.25f* 2.0*M_PI;
    glm::vec2 phasorNoise = eval_noise(uv,_f,_b);
    glm::vec2 dir = glm::vec2(cos(o),sin(o));
    float phi = glm::atan(phasorNoise.y,phasorNoise.x);
    //float I = length(phasorNoise);
    //float angle = texture(iChannel0,fragCoord/iResolution.xy ).x;
    glm::vec3 phasorfield = glm::vec3(sin(phi)*0.3 +0.5);

    //printf("(%f, %f, %f): x = %f | y = %f\n", xCoord, yCoord, zCoord, phasorfield.x, phasorfield.y);

    return (phasorfield.x * 2.0f) - 1.0f;
}

