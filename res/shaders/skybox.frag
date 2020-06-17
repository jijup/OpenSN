#version 330 core

in vec3 texUVSB;

out vec4 color;

uniform samplerCube skybox;

void main() {
    color = texture(skybox, texUVSB);
}
