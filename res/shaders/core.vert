#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec3 vColor;
out vec2 texUV;

uniform mat4 transform;
uniform sampler2D noiseTexture;
uniform sampler2D normalMap;
uniform sampler2D noiseTextureColor;

// Bump Mapping
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;
out mat3 TBN;
out vec3 tangentLightPos;
out vec3 tangentViewPos;
out vec3 tangentFragPos;
out vec3 fragPos;


void main() {

    int mode = 4;           // 1 - heightmap | 2 - model | 3 - normal mapping | 4 - parallax occlusion mapping
    if (mode == 1) {
        float h = (texture(noiseTexture, uv).r + 1.0f) / 2.0f;
        vec3 fragPos = vec3(position) + vec3(0.0f, h, 0.0f);
        gl_Position = transform * (vec4(fragPos, 1.0f));
    } else if (mode == 2) {
        vec3 fragPos = vec3(position);
        gl_Position = transform * (vec4(fragPos, 1.0f));

        vColor = normal;
        //texUV = vec2(uv.x, 1.0 - uv.y);
        texUV = vec2(uv.x, uv.y);
    } else if (mode == 3) {
        fragPos = vec3(model * vec4(position, 1.0));
        texUV = uv;

        mat3 normalMatrix = transpose(inverse(mat3(model)));
        vec3 T = normalize(normalMatrix * tangent);
        vec3 N = normalize(normalMatrix * normal);
        T = normalize(T - dot(T, N) * N);
        vec3 B = cross(N, T);
        TBN = transpose(mat3(T, B, N));

        vec3 lightPosWS = vec3(10.5, 10.5, 10.5);
        vec3 lightPos = (view * vec4(lightPosWS, 1.0)).xyz;
        tangentLightPos = TBN * lightPos;
        tangentViewPos  = TBN * viewPos;
        tangentFragPos  = TBN * vec3(model * vec4(position, 0.0));

        gl_Position = projection * view * model * vec4(position, 1.0);
    } else if (mode == 4) {
        fragPos = vec3(model * vec4(position, 1.0));
        texUV = uv;

        vec3 T = normalize(mat3(model) * tangent);
        vec3 B = normalize(mat3(model) * bitangent);
        vec3 N = normalize(mat3(model) * normal);
        TBN = transpose(mat3(T, B, N));

        vec3 lightPosWS = vec3(10.5, 10.5, 10.5);
        //vec3 lightPos = (view * vec4(lightPosWS, 1.0)).xyz;
        vec3 lightPos = (vec4(lightPosWS, 1.0)).xyz;
        tangentLightPos = TBN * lightPos;
        tangentViewPos  = TBN * viewPos;
        tangentFragPos  = TBN * fragPos;

        gl_Position = projection * view * model * vec4(position, 1.0);
    }
}