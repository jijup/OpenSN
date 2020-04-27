#version 330 core
in vec3 vColor;
in vec2 texUV;

out vec4 fColor;

//uniform sampler2D marbleTexture;
uniform sampler2D marbleTexture;

void main()
{
    // Linearly interpolate between both textures (second texture is only slightly combined)
    fColor = texture(marbleTexture, texUV);
}