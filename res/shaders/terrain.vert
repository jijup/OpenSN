#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 fragPos;                   //out vec3 vColor;
out vec2 texUV;
out float waterHeight;

uniform mat4 transform;
uniform sampler2D noiseTexture;

void main() {

    float water = 0.45f;
    float h = texture(noiseTexture, uv).r;
    h = max(h, water);

    fragPos = vec3(position) + vec3(0.0f, h, 0.0f);
    gl_Position = transform * (vec4(fragPos, 1.0f));
    //texUV = vec2(uv.x, 1.0 - uv.y);
    texUV = vec2(uv.x, uv.y);

    waterHeight = water;
}
