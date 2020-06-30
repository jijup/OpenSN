#version 330 core

// Uniforms
uniform sampler2D grass;
uniform sampler2D rock;
uniform sampler2D sand;
uniform sampler2D snow;
uniform sampler2D water;
//uniform sampler2D lunar;

uniform sampler2D noiseTexture;
uniform float waveMotion;
uniform vec3 viewPos;

in vec3 fragPos;
in vec2 texUV;
in float waterHeight;

out vec4 color;

void main() {

    // Directional light source
    //vec3 lightPos = vec3(1.0f, 1.0f, 3.0f);
    vec3 lightPos = vec3(1.0f, 1.0f, 1.0f);

    // Texture size in pixels
    ivec2 size = textureSize(noiseTexture, 0);

    // Calculate distorted wave positions
    vec2 layeredWaterCoordinates = texture(water, vec2(texUV.x + waveMotion, texUV.y)).rg * 0.01f;
    layeredWaterCoordinates = texUV + vec2(layeredWaterCoordinates.x, layeredWaterCoordinates.y + waveMotion);

    // Calculate surface normal N
    vec3 A = vec3(texUV.x + 1.0f / size.x, texUV.y, textureOffset(noiseTexture, texUV, ivec2(1, 0)));
    vec3 B = vec3(texUV.x - 1.0f / size.x, texUV.y, textureOffset(noiseTexture, texUV, ivec2(-1, 0)));
    vec3 C = vec3(texUV.x, texUV.y + 1.0f / size.y, textureOffset(noiseTexture, texUV, ivec2(0, 1)));
    vec3 D = vec3(texUV.x, texUV.y - 1.0f / size.y, textureOffset(noiseTexture, texUV, ivec2(0, -1)));
    vec3 normal = normalize(cross(normalize(A - B), normalize(C - D)));

    // Adjust Slopes & Levels
    float denom = 1.0f / size.x;
    float slope = 0.0f;
    slope = max(slope, (A.y - fragPos.y) / denom);
    slope = max(slope, (B.y - fragPos.y) / denom);
    slope = max(slope, (C.y - fragPos.y) / denom);
    slope = max(slope, (D.y - fragPos.y) / denom);

    // Slopes & Levels - Earth (fBm2DTexture)
    float tempWaterHeight = waterHeight;
    float sandLevel = waterHeight + 0.03f;
    float grassLevel = sandLevel + 0.02f;
    float snowLevel = 0.85f;
    float sandSlope = 0.7f;
    float snowSlope = 0.85f;
    vec4 col = texture(sand, texUV);
    bool lunarControl = false;
    vec2 tempAdj = vec2(0.1f, 0.1f);

    /*
    // Slopes & Levels - Lunar (HybridMultifractal2DTexture)
    float tempWaterHeight = 0.0f;
    float sandLevel = tempWaterHeight + 0.0f;
    float grassLevel = sandLevel;
    float snowLevel = 0.0f;
    float sandSlope = 0.0f;
    float snowSlope = 0.0f;
    vec4 col = texture(lunar, texUV);
    bool lunarControl = true;
    */

    // Texture according to height and slope
    float height = texture(noiseTexture, texUV).r;

    // Calculate ambient lighting factor
    float ambient = 0.05f;
    float diffuse_coefficient = 0.2f;
    float specular_coefficient = 0.2f;
    float specularPower = (height / 1.0f) * 10.0f;

    if (!lunarControl) {

        // Texture with water if below water height, else texture with sand or blend
        float eightDistance = (sandLevel - tempWaterHeight) / 8.0f;
        if (height < tempWaterHeight) {
            col = texture(water, layeredWaterCoordinates);
            specularPower = 5.0f;
            specular_coefficient = 0.1f;
        } else if (height < (tempWaterHeight + eightDistance)) {
            float pos = height - tempWaterHeight;
            float posScaled = pos / eightDistance;
            col = (texture(sand, texUV) * (posScaled)) + (texture(water, layeredWaterCoordinates) * (1 - posScaled));
        } else if (height > tempWaterHeight && height < sandLevel && slope < sandSlope) {
            col = texture(sand, texUV);
            specularPower = 0.0f;
            specular_coefficient = 0.0f;
        }

        // Texture with grass
        if (height > sandLevel && height < grassLevel) {
            //col = texture(grass, texUV);
            specularPower = 5.0f;

            // Calculate blend factor
            //float halfDistance = (grassLevel - sandLevel) / 2.0f;
            float halfDistance = (grassLevel - sandLevel) / 2.0f;

            if (height < (sandLevel + halfDistance)) {

                // Blend with sand
                float pos = height - sandLevel;
                float posScaled = pos / halfDistance;
                col = (texture(grass, texUV) * (posScaled)) + (texture(sand, texUV) * (1 - posScaled));
            } else {
                col = texture(grass, texUV);
            }
        }

        // Texture with rock
        if (height > grassLevel) {
            col = texture(rock, texUV);
            specularPower = 0.0f;
            specular_coefficient = 0.0f;

            // Calculate blend factor
            float quarterDistance = (snowLevel - grassLevel) / 4.0f;
            float eightDistance = quarterDistance / 2.0f;

            if (height < (grassLevel + eightDistance)) {
                float pos = height - grassLevel;
                float posScaled = pos / eightDistance;
                col = (texture(rock, texUV) * (posScaled)) + (texture(grass, texUV) * (1 - posScaled));
            } else if (height > (snowLevel - quarterDistance)) {

                // Blend with snow
                float pos = height - (snowLevel - quarterDistance);
                float posScaled = pos / quarterDistance;
                col = (texture(snow, texUV) * (posScaled)) + (texture(rock, texUV) * (1 - posScaled));
            }
        }

        // Texture with snow
        if (height > snowLevel && slope < snowSlope) {
            col = texture(snow, texUV);
            specularPower = 100.0f;
        }
    }

    // Calculate diffuse lighting factor
    vec3 lightDir = normalize(lightPos - fragPos);
    float diffuse = diffuse_coefficient * max(0.0f, -dot(normal, lightDir));

    // Calculate specular lighting factor
    vec3 view_direction = viewPos - fragPos;
    vec3 halfway = normalize(lightDir + view_direction);
    float specular = specular_coefficient * max(0.0f, pow(dot(normal, halfway), specularPower));


    if (diffuse > 0.0f) {
        col += (ambient + diffuse + specular);
    } else {
        col += (ambient + diffuse);
    }


    //color = vec4(col);
    color = col;
}
