#version 330 core
in vec3 vColor;
in vec2 texUV;

out vec4 fColor;

//uniform sampler2D marbleTexture;
uniform sampler2D marbleTexture;

void main() {
    fColor = texture(marbleTexture, texUV);
}