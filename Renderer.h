/**
 * Renderer.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of GLFW, ImGui & OpenGL-based rendering.
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "Noise.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "ImageOutput.h"
#include "PrimePlot.h"
#include "Analysis.h"
#include "Texture.h"

#include <memory>
#include <OpenGP/types.h>
#include <OpenGP/GL/Texture.h>
#include <OpenGP/GL/GPUMesh.h>
#include <OpenGP/GL/Shader.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/string_cast.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stb_image/stb_image.h>
#include <stb_image/stb_image_write.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#define PI 3.14159265

class Renderer {
public:
    Renderer();
    Renderer(int width, int height, int noiseType, int pairingFunction, int saveImageFlag,
             int applicationType, int analysisFlag, int amplitudeAnalysisFlag, int fourierAnalysisFlag);
    ~Renderer();

    // Generate filenames
    std::string generateFilenames(int filenameType);

    // Setup OpenGL buffers
    int setupBuffersMesh();
    int setupBuffersMeshSkybox();
    int setupBuffersMeshPlanet();

    // Set ImGui text rendering variables
    int updateImguiText();

    // Saves framebuffer as PNG
    int savePNG(std::string filename, GLFWwindow* w);

    // Saves framebuffer as BMP
    int saveBMP(std::string filename, GLFWwindow* w);

    // Render
    int renderApplication();

private:

    ///----- Class instances
    Noise *NoiseInstance;
    Analysis *AnalysisInstance;
    ImageOutput *imageInstance;
    Mesh meshInstance;
    Texture textureInstance;

    ///----- Noise Generation
    int width;                  // X dimensions
    int height;                 // Y dimensions
    int noiseType;              // Noise to generate (0 - Perlin | 1 - Gabor | 2 - Marble )
    int pairingFunction;        // Pairing function to use (0 - Linear | 1 - Cantor | 2 - Szudzik | 3 - Rosenberg-Strong)
    bool saveImageFlag;         // Flag to determine whether the noise generated should be saved as an image

    ///----- Application Variables
    int applicationType;
    //GLuint textures[8];
    GLuint *textures;
    GLfloat waveMotion;

    ///----- Analysis variables
    bool analysisFlag;
    bool amplitudeAnalysisFlag;
    bool fourierAnalysisFlag;

    ///----- Rendering
    const char* imguiNoiseType;
    const char* imguiPairingFunction;
    const char* imguiApplicationType;
    bool ImguiActiveFlag;

    // Framebuffer variables
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    GLuint sbVBO;
    GLuint sbVAO;
    GLuint sbEBO;
    GLuint plVBO;
    GLuint plVAO;
    GLuint plEBO;

    // ImGui slider adjustment variables
    glm::vec3 translationStart;
    glm::vec3 rotationStart;
    glm::vec3 scaleStart;

    glm::vec3 cameraPosition;
    glm::vec3 cameraLookatOrigin;
    glm::vec3 cameraUp;

    GLfloat fovFactor;
    GLfloat rotateFactor;
    GLfloat scaleFactor;

    glm::vec3 planetLocation;
    glm::vec3 planetScaleVec;
    GLfloat planetScale;

    GLenum err;

};



