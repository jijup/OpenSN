#version 330 core

in vec3 vColor;
in vec2 texUV;

out vec4 fColor;

uniform sampler2D noiseTexture;

void main() {
    fColor = texture(noiseTexture, texUV);
}