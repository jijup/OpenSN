#version 330 core

in vec3 vColor;
in vec2 texUV;

out vec4 fColor;

uniform sampler2D noiseTexture;
uniform sampler2D normalMap;
uniform sampler2D noiseTextureColor;

// Bump mapping
in mat3 TBN;
in vec3 tangentLightPos;
in vec3 tangentViewPos;
in vec3 tangentFragPos;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    float heightScale = 1.0;

    float height =  texture(noiseTexture, texCoords).r;
    return texCoords - viewDir.xy * (height * heightScale);
}

vec2 ParallaxMappingOcclusion(vec2 texCoords, vec3 viewDir)
{
    //float heightScale = 0.5;
    float heightScale = 1.0;

    // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 32;

    //float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
    float numLayers = maxLayers * (1 - abs(dot(vec3(0.0, 0.0, 1.0), viewDir))) + minLayers * abs(dot(vec3(0.0, 0.0, 1.0), viewDir));

    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * heightScale;
    vec2 deltaTexCoords = P / numLayers;

    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(noiseTexture, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue) {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(noiseTexture, currentTexCoords).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }

    //return currentTexCoords;  // Steep parallax mapping

    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(noiseTexture, prevTexCoords).r - currentLayerDepth + layerDepth;

    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}

float PrimeGradientNoise(vec3 point) {



    return 0.0;
}

void main() {

    // Heightmap [1]
    //float h = texture(noiseTexture, texUV).r;
    //float r = (67.0 - 42.0 * h) / 255.0;
    //float g = (198.0 - 170.0 * h) / 255.0;
    //float b = (172.0 - 88.0 * h) / 255.0;
    //fColor = vec4(r,g,b,1.0);


    // Model [2]
    //fColor = texture(noiseTextureColor, texUV);


    // Bump mapping [3]
    // obtain normal from normal map in range [0,1]
    /*vec3 normal = texture(noiseTexture, texUV).rgb;
    // transform normal vector to range [-1,1]
    //normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space

    // get diffuse color
    vec3 color = texture(noiseTexture, texUV).rgb;

    // ambient
    vec3 ambient = 0.1 * color;

    // diffuse
    vec3 tangentLightPos = vec3(2.0, 2.0, 2.0);
    vec3 lightDir = normalize(tangentLightPos - tangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    // specular
    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 4.0);

    vec3 specular = vec3(0.2) * spec;
    fColor = vec4(ambient + diffuse + specular, 1.0);*/


    // Parallax Mapping [4]
    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);
    vec2 texCoords = texUV;

    //texCoords = ParallaxMapping(texUV,  viewDir);
    texCoords = ParallaxMappingOcclusion(texUV,  viewDir);
    //if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
    //    discard;

    vec3 normal = texture(normalMap, texCoords).rgb;
    //normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(normal);

    // get diffuse color
    vec3 color = texture(noiseTextureColor, texCoords).rgb;
    //vec3 color = texture(noiseTexture, texCoords).rgb;
    //vec3 color = vec3(0.5, 0.5, 0.5);

    // ambient
    //vec3 ambient = color * 0.25;
    vec3 ambient = color * 0.1;

    // diffuse
    vec3 lightDir = normalize(tangentLightPos - tangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    //vec3 diffuse = diff * color * 0.5;
    vec3 diffuse = diff * color;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    //vec3 specular = vec3(0.25) * spec;
    vec3 specular = vec3(0.25) * spec;
    fColor = vec4(ambient + diffuse + specular, 1.0);

    // obtain normal from normal map
    /*vec3 off = vec3(-0.001,0.0,0.001);
    vec2 size = vec2(1.0,0.0);
    vec4 temp = texture(noiseTexture, texCoords);
    float s11 = temp.x;
    float s01 = texture(noiseTexture, texCoords + off.xy).x;
    float s21 = texture(noiseTexture, texCoords + off.zy).x;
    float s10 = texture(noiseTexture, texCoords + off.yx).x;
    float s12 = texture(noiseTexture, texCoords + off.yz).x;

    vec3 va = normalize(vec3(size.x, s21-s01, size.y));
    vec3 vb = normalize(vec3(size.y, s12-s10, -size.x));

    //vec3 va = normalize(vec3(size.xy,s21-s01));
    //vec3 vb = normalize(vec3(size.yx,s12-s10));

    vec4 bump = vec4( cross(va,vb), s11 );
    vec3 normal = normalize(bump.xyz);*/
}