#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 vColor;
out vec2 texUV;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(position, 1.0f);
    vColor = normal;
    texUV = vec2(uv.x, 1.0 - uv.y);
}