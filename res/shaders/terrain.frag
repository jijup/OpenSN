#version 330 core

// Uniforms
//uniform sampler2D grass;
//uniform sampler2D rock;
//uniform sampler2D sand;
//uniform sampler2D snow;
//uniform sampler2D water;
//uniform sampler2D lunar;

// In
in vec3 fragPos;        // in vec3 vColor;
in vec2 uv;             // in vec2 texUV;

// Out
out vec4 color;         // out vec4 fColor;

//uniform float waveMotion;
//uniform vec3 viewPos;
uniform sampler2D noiseTex;     // uniform sampler2D marbleTexture;

void main() {

    // Directional light source
    //vec3 lightPos = vec3(1.0f, 1.0f, 3.0f);
    vec3 lightPos = vec3(1.0f, 1.0f, 1.0f);

    // Texture size in pixels
    ivec2 size = textureSize(noiseTex, 0);

    /*
    // Calculate distorted wave positions
    vec2 layeredWaterCoordinates = texture(water, vec2(uv.x + waveMotion, uv.y)).rg * 0.01f;
    layeredWaterCoordinates = uv + vec2(layeredWaterCoordinates.x, layeredWaterCoordinates.y + waveMotion);
    */

    // Calculate surface normal N
    vec3 A = vec3(uv.x + 1.0f / size.x, uv.y, textureOffset(noiseTex, uv, ivec2(1, 0)));
    vec3 B = vec3(uv.x - 1.0f / size.x, uv.y, textureOffset(noiseTex, uv, ivec2(-1, 0)));
    vec3 C = vec3(uv.x, uv.y + 1.0f / size.y, textureOffset(noiseTex, uv, ivec2(0, 1)));
    vec3 D = vec3(uv.x, uv.y - 1.0f / size.y, textureOffset(noiseTex, uv, ivec2(0, -1)));
    vec3 normal = normalize( cross(normalize(A - B), normalize(C - D)) );

    // Adjust Slopes & Levels
    float denom = 1.0f / size.x;
    float slope = 0.0f;
    slope = max(slope, (A.y - fragPos.y) / denom);
    slope = max(slope, (B.y - fragPos.y) / denom);
    slope = max(slope, (C.y - fragPos.y) / denom);
    slope = max(slope, (D.y - fragPos.y) / denom);

    /*
    // Slopes & Levels - Earth (fBm2DTexture)
    float tempWaterHeight = waterHeight;
    float sandLevel = waterHeight + 0.02f;
    float grassLevel = sandLevel + 0.07f;
    float snowLevel = 1.0f;
    float sandSlope = 0.7f;
    float snowSlope = 0.85f;
    vec4 col = texture(sand, uv);
    bool lunarControl = false;
    vec2 tempAdj = vec2(0.1f, 0.1f);
    */

    /*
    // Slopes & Levels - Lunar (HybridMultifractal2DTexture)
    float tempWaterHeight = 0.0f;
    float sandLevel = tempWaterHeight + 0.0f;
    float grassLevel = sandLevel;
    float snowLevel = 0.0f;
    float sandSlope = 0.0f;
    float snowSlope = 0.0f;
    vec4 col = texture(lunar, uv);
    bool lunarControl = true;
    */

    // Texture according to height and slope
    vec4 col = texture(noiseTex, uv);
    float height = (texture(noiseTex, uv).r + 1.0f) / 2.0f;


    // Calculate colour
    col = texture(noiseTex, uv);

    color = vec4(height, height, height, 1.0f);
}
