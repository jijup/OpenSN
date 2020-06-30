#version 330 core

layout (location = 0) in vec3 positionSB;
//in vec3 vposition;

out vec3 texUVSB;

uniform mat4 projectionSB;
uniform mat4 viewSB;

uniform samplerCube skybox;

void main() {
    /*texUVSB = positionSB;
    vec4 pos = viewSB * vec4(positionSB, 1.0);
    gl_Position = pos.xyww;*/


    texUVSB = positionSB;
    vec4 pos = projectionSB * viewSB * vec4(positionSB, 1.0);
    gl_Position = pos.xyww;
}
