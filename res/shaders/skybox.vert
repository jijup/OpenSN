#version 330 core
in vec3 vposition;

out vec3 uvw;

//uniform mat4 V;
//uniform mat4 P;

uniform mat4 transform;

void main() {
    // Cubemaps follow a LHS coordinate system
    uvw = vec3(vposition.x, -vposition.z, -vposition.y);
    gl_Position = transform*vec4(10.0*vposition, 1.0);
}
