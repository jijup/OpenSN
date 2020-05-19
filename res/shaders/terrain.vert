#version 330 core

uniform sampler2D noiseTex;

in vec3 vposition;
in vec2 vtexcoord;

out vec3 fragPos;
out vec2 uv;

//uniform mat4 M;
//uniform mat4 V;
//uniform mat4 P;
uniform mat4 transform;

void main() {

    uv = vtexcoord;

    // Earth scene
    float water = 0.7f;

    // Lunar scene
    //float water = 0.0f;

    // Calculate height
    float h = (texture(noiseTex, uv).r + 1.0f) / 2.0f;
    h = max(h, water);

    // Set fragment position
    fragPos = vposition.xyz + vec3(0,0,h);

    // Set gl_Position
    gl_Position = transform * vec4(fragPos, 1.0f);

    // Set height of water
    //waterHeight = water;
}
