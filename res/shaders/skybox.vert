#version 330 core

layout (location = 0) in vec3 positionSB;
//in vec3 vposition;

out vec3 texUVSB;

uniform mat4 projectionSB;
uniform mat4 viewSB;

void main() {
    texUVSB = positionSB;

    vec4 pos = projectionSB * viewSB * vec4(positionSB, 1.0);
    //vec4 pos = projectionSB * viewSB * vec4(positionSB.x, positionSB.y, positionSB.z, 1.0);
    gl_Position = pos.xyww;


    // Use with glDepthFunc(GL_LEQUAL) then re-enable glDepthFunc(GL_LESS).
    //vec4 pos = projectionSB * viewSB * vec4(positionSB, 1.0);
    //gl_Position = pos.xywz;
}
