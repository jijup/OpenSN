/**
 * Renderer.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of GLFW & OpenGL-based rendering with ImGui.
 */

#include "Renderer.h"

Renderer::Renderer() {

    this->waveMotion = 0.0f;

    // Object initial location
    /*this->translationStart = glm::vec3(0.000f, 0.000f, 0.000f);
    this->rotationStart = glm::vec3(1.000f, 0.000f, 0.000f);
    this->scaleStart = glm::vec3(0.075f, 0.075f, 0.075f);

    // Camera initial location
    this->cameraPosition   = glm::vec3(0.0f, 1.0f,  20.0f);
    this->cameraLookatOrigin   = glm::vec3(0.0f, 0.0f,  0.0f);
    this->cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    // Initial factors
    this->fovFactor = 90.0f;
    this->rotateFactor = 0.0f;
    this->scaleFactor = 1.0f;*/

    this->translationStart = glm::vec3(0.000f, 0.000f, 0.000f);
    this->rotationStart = glm::vec3(1.000f, 0.000f, 0.000f);
    this->scaleStart = glm::vec3(1.0f, 1.0f, 1.0f);

    // Camera initial location
    this->cameraPosition   = glm::vec3(0.0f, 0.0f,  2.0f);
    this->cameraLookatOrigin   = glm::vec3(0.0f, 0.0f,  0.0f);
    this->cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    // Initial factors
    this->fovFactor = 90.0f;
    this->rotateFactor = 0.0f;
    this->scaleFactor = 1.0f;

    this->planetLocation = glm::vec3(0.5f, 2.0f, -0.5f);
    this->planetScale = 0.1f;

    // Initial dimensions
    this->width = 1000;
    this->height = 1000;

    // Runtime information
    this->noiseType = 0;
    this->pairingFunction = 1;
    this->applicationType = 0;

    // Flags
    this->saveImageFlag = 1;
    this->analysisFlag = 1;
    this->amplitudeAnalysisFlag = 0;
    this->fourierAnalysisFlag = 1;

    // ImGui setup
    this->ImguiActiveFlag = true;
    updateImguiText();
}

Renderer::Renderer(int width, int height, int noiseType, int pairingFunction, int saveImageFlag,
                   int applicationType, int analysisFlag, int amplitudeAnalysisFlag, int fourierAnalysisFlag) {

    this->waveMotion = 0.0f;

    if (applicationType == 0) {
        this->translationStart = glm::vec3(0.000f, 0.000f, 0.000f);
        this->rotationStart = glm::vec3(0.000f, 1.000f, 0.000f);
        this->scaleStart = glm::vec3(0.075f, 0.075f, 0.075f);

        // Camera initial location
        this->cameraPosition   = glm::vec3(0.0f, 1.0f,  20.0f);
        this->cameraLookatOrigin   = glm::vec3(0.0f, 0.0f,  0.0f);
        this->cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    } else if (applicationType == 1) {
        this->translationStart = glm::vec3(0.000f, 0.000f, 0.000f);
        this->rotationStart = glm::vec3(1.000f, 0.000f, 0.000f);
        this->scaleStart = glm::vec3(1.0f, 1.0f, 1.0f);

        // Camera initial location
        this->cameraPosition   = glm::vec3(0.0f, 0.0f,  1.0f);
        this->cameraLookatOrigin   = glm::vec3(0.0f, 0.0f,  0.0f);
        this->cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

        this->planetLocation = glm::vec3(0.5f, 2.0f, -0.5f);
        this->planetScaleVec = glm::vec3(1.0f, 1.0f, 1.0f);
        this->planetScale = 0.1f;
    }

    //this->textures = new GLuint[8];

    // Initial factors
    this->fovFactor = 90.0f;
    this->rotateFactor = 0.0f;
    this->scaleFactor = 1.0f;

    // Initial dimensions
    this->width = width;
    this->height = height;

    // Runtime information
    this->noiseType = noiseType;
    this->pairingFunction = pairingFunction;
    this->applicationType = applicationType;

    // Flags
    this->saveImageFlag = saveImageFlag;
    this->analysisFlag = analysisFlag;
    this->amplitudeAnalysisFlag = amplitudeAnalysisFlag;
    this->fourierAnalysisFlag = fourierAnalysisFlag;

    // ImGui setup
    this->ImguiActiveFlag = true;
    updateImguiText();
}

Renderer::~Renderer() {}

/*
 * Generates a filename dependent on the current parameters.
 *
 * Returns:
 *      string: filename to save application output as
 */
std::string Renderer::generateFilenames(int filenameType) {

    // Pairing function
    std::string title = "";
    if (this->pairingFunction == 0) {
        title = "Linear";
    } else if (this->pairingFunction  == 1) {
        title = "Cantor";
    } else if (this->pairingFunction  == 2) {
        title = "Szudzik";
    } else if (this->pairingFunction  == 3) {
        title = "RosenbergStrong";
    } else if (this->pairingFunction  == 4) {
        title = "Original";
    } else {
        // TODO: Throw error
    }

    if (filenameType == 0) {

        // Noise type
        if (this->noiseType == 0) {
            title = "Perlin_Noise_" + title;
        } else if (this->noiseType == 1) {
            title = "Gabor_Noise";
        } else if (this->noiseType == 2) {
            title = "Perlin_Marble_Noise_" + title;
        } else if (this->noiseType == 3) {
            title = "Worley_Noise";
        } else if (this->noiseType == 4) {
            title = "Testing_New_Noise_" + title;
        } else if (this->noiseType == 5) {
            title = "Perlin_Splatter_Noise_" + title;
        } else if (this->noiseType == 6) {
            title = "Perlin_Wood_Noise_" + title;
        } else if (this->noiseType == 7) {
            title = "Primed_Gradient_Noise";
        } else if (this->noiseType == 8) {
            title = "Primed_Density_Noise";
        } else if (this->noiseType == 9) {
            title = "Better_Gradient_Noise";
        } else if (this->noiseType == 10) {
            title = "Wavelet_Noise";
        } else if (this->noiseType == 11) {
            title = "Phasor_Noise";
        } else {
            // TODO: Throw error
        }
    } else if (filenameType == 1) {

        // Noise type
        if (this->noiseType == 0) {
            title = "Perlin_" + title;
        } else if (this->noiseType == 1) {
            //title = "Gabor_" + title;
            title = "Gabor";
        } else if (this->noiseType == 2) {
            title = "Perlin_Marble_" + title;
        } else if (this->noiseType == 3) {
            //title = "Worley_" + title;
            title = "Worley";
        } else if (this->noiseType == 4) {
            title = "Testing_New_" + title;
        } else if (this->noiseType == 5) {
            title = "Perlin_Splatter_" + title;
        } else if (this->noiseType == 6) {
            title = "Perlin_Wood_" + title;
        } else if (this->noiseType == 7) {
            title = "Primed_Gradient";
        } else if (this->noiseType == 8) {
            title = "Primed_Density";
        } else if (this->noiseType == 9) {
            title = "Better_Gradient";
        } else if (this->noiseType == 10) {
            title = "Wavelet";
        } else if (this->noiseType == 11) {
            title = "Phasor";
        } else {
            // TODO: Throw error
        }

        // Application type
        if (this->applicationType == 0) {
            title = "Vase_" + title;
        } else if (this->applicationType == 1) {
            title = "ProceduralLandscape_" + title;
        } else {
            // TODO: Throw error
        }
    } else {
        // TODO: Throw error
    }

    return title;
}

/*
 * Sets up buffers for meshes loaded from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Renderer::setupBuffersMesh() {

    // Generate buffers
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    if (this->applicationType == 0) {
        // Setup VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        //glBufferData(GL_ARRAY_BUFFER, this->meshInstance.numIndices * 8 * sizeof(GLfloat), this->meshInstance.verticesMesh, GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, this->meshInstance.numIndices * 14 * sizeof(GLfloat), this->meshInstance.verticesMesh, GL_STATIC_DRAW);///

        // Setup EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->meshInstance.numIndices * sizeof(GLuint), this->meshInstance.indicesMesh, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid *) 0 );
        glEnableVertexAttribArray(0);

        // Color/Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture Coordinate attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Tangent
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid *)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);

        // Bitangent
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid *)(11 * sizeof(float)));
        glEnableVertexAttribArray(4);
    } else if (this->applicationType == 1) {

        // Setup VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->meshInstance.numIndices * 8 * sizeof(GLfloat), this->meshInstance.verticesMesh, GL_STATIC_DRAW);

        // Setup EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->meshInstance.numIndices * sizeof(GLuint), this->meshInstance.indicesMesh, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0 );
        glEnableVertexAttribArray(0);

        // Color/Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture Coordinate attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    glBindVertexArray(0);

    return 0;
}

/*
 * Sets up buffers for meshes loaded from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Renderer::setupBuffersMeshPlanet() {

    // Generate buffers
    glGenVertexArrays(1, &this->plVAO);
    glGenBuffers(1, &this->plVBO);
    glGenBuffers(1, &this->plEBO);

    glBindVertexArray(this->plVAO);

    // Setup VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->plVBO);
    glBufferData(GL_ARRAY_BUFFER, this->meshInstance.numIndicesPlanet * 8 * sizeof(GLfloat), this->meshInstance.verticesMeshPlanet, GL_STATIC_DRAW);

    // Setup EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->plEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->meshInstance.numIndicesPlanet * sizeof(GLuint), this->meshInstance.indicesMeshPlanet, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0 );
    glEnableVertexAttribArray(0);

    // Color/Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture Coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    return 0;
}

/*
 * Sets up buffers for meshes loaded from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Renderer::setupBuffersMeshSkybox() {

    /*// Generate buffers
    glGenVertexArrays(1, &this->sbVAO);
    glGenBuffers(1, &this->sbVBO);
    glGenBuffers(1, &this->sbEBO);

    glBindVertexArray(this->sbVAO);

    // Setup VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->sbVBO);
    glBufferData(GL_ARRAY_BUFFER, this->meshInstance.numIndicesSkybox * 8 * sizeof(GLfloat), this->meshInstance.verticesMeshSkybox, GL_STATIC_DRAW);

    // Setup EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->sbEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->meshInstance.numIndicesSkybox * sizeof(GLuint), this->meshInstance.indicesMeshSkybox, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0 );
    glEnableVertexAttribArray(0);

    // Color/Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture Coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    return 0;*/

    // Generate buffers
    glGenVertexArrays(1, &this->sbVAO);
    glGenBuffers(1, &this->sbVBO);

    glBindVertexArray(this->sbVAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->sbVBO);
    glBufferData(GL_ARRAY_BUFFER, this->meshInstance.numIndicesSkybox * 3 * sizeof(GLfloat), this->meshInstance.verticesMeshSkybox, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

    glBindVertexArray(0);

    return 0;
}

/*
 * Sets ImGui text variables for noise type, pairing function and application type.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Renderer::updateImguiText() {

    // Pairing function
    if (this->pairingFunction == 0) {
        imguiPairingFunction = "Pairing Function: Linear";
    } else if (this->pairingFunction  == 1) {
        imguiPairingFunction = "Pairing Function: Cantor";
    } else if (this->pairingFunction  == 2) {
        imguiPairingFunction = "Pairing Function: Szudzik";
    } else if (this->pairingFunction  == 3) {
        imguiPairingFunction = "Pairing Function: Rosenberg-Strong";
    } else if (this->pairingFunction  == 4) {
        imguiPairingFunction = "Pairing Function: Original Perlin";
    } else {
        // TODO: Throw error
    }

    if (this->noiseType == 1 || this->noiseType == 3 || this->noiseType == 7 || this->noiseType == 8 || this->noiseType == 9 || this->noiseType == 10 || this->noiseType == 11) {
        imguiPairingFunction = "N/A";
    }

    // Noise type
    if (this->noiseType == 0) {
        imguiNoiseType = "Noise Type: Perlin";
    } else if (this->noiseType == 1) {
        imguiNoiseType = "Noise Type: Gabor";
    } else if (this->noiseType == 2) {
        imguiNoiseType = "Noise Type: Perlin (marble)";
    } else if (this->noiseType == 3) {
        imguiNoiseType = "Noise Type: Worley";
    } else if (this->noiseType == 4) {
        imguiNoiseType = "Noise Type: Testing New Noise";
    } else if (this->noiseType == 5) {
        imguiNoiseType = "Noise Type: Perlin (splatter)";
    } else if (this->noiseType == 6) {
        imguiNoiseType = "Noise Type: Perlin (wood)";
    } else if (this->noiseType == 7) {
        imguiNoiseType = "Noise Type: Primed Gradient";
    } else if (this->noiseType == 8) {
        imguiNoiseType = "Noise Type: Primed Density";
    } else if (this->noiseType == 9) {
        imguiNoiseType = "Noise Type: Better Gradient";
    } else if (this->noiseType == 10) {
        imguiNoiseType = "Noise Type: Wavelet";
    } else if (this->noiseType == 11) {
        imguiNoiseType = "Noise Type: Phasor";
    } else {
        // TODO: Throw error
    }

    // Application type
    if (this->applicationType == 0) {
        imguiApplicationType = "Application: Vase";
    } else if (this->applicationType == 1) {
        imguiApplicationType = "Application: Procedural Landscape";
    } else {
        // TODO: Throw error
    }

    return 0;
}

/*
 * Saves framebuffer as PNG
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Renderer::savePNG(std::string filename, GLFWwindow* w) {

    printf("\nAttempting to write framebuffer to PNG.\n");

    int width, height;
    glfwGetFramebufferSize(w, &width, &height);

    GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * width;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    GLsizei bufferSize = stride * height;

    std::vector<char> buffer(bufferSize);

    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_FRONT);
    //glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

    stbi_flip_vertically_on_write(true);
    stbi_write_png(filename.c_str(), width, height, nrChannels, buffer.data(), stride);

    printf("    PNG written: %s\n", filename.c_str());
    printf("Successfully wrote framebuffer to PNG.\n");

    return 0;
}

/*
 * Saves framebuffer as BMP
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Renderer::saveBMP(std::string filename, GLFWwindow* w) {
    printf("\nAttempting to write framebuffer to BMP.\n");

    int width, height;
    glfwGetFramebufferSize(w, &width, &height);

    // Specify layout
    GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * width;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    GLsizei bufferSize = stride * height;

    std::vector<char> buffer(bufferSize);

    // Read pixels
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

    // Save as BMP
    stbi_flip_vertically_on_write(true);
    stbi_write_bmp(filename.c_str(), width, height, nrChannels, buffer.data());

    printf("    BMP written: %s\n", filename.c_str());
    printf("Successfully wrote framebuffer to BMP.\n");
    return 0;
}

/*
 * Render application.
 */
int Renderer::renderApplication() {

    // Generate title
    std::string fileNoise = Renderer::generateFilenames(0);
    std::string fileApp = Renderer::generateFilenames(1);

    /// ========================== GENERATE NOISE/RUN ANALYSIS/SAVE IMAGE ==========================
    std::vector<Noise::Point> noiseVec;
    int generateNoise = 0;
    if (generateNoise == 0) {
        std::vector<Noise::Point> noise;
        if (this->noiseType == 0) {
            noise = this->NoiseInstance->generatePerlin(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 1) {
            noise = this->NoiseInstance->generateGabor(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 2) {
            noise = this->NoiseInstance->generateMarble(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 3) {
            noise = this->NoiseInstance->generateWorley(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 4) {
            noise = this->NoiseInstance->generateExperiental(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 5) {
            noise = this->NoiseInstance->generateSplatter(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 6) {
            noise = this->NoiseInstance->generateWood(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 7) {
            noise = this->NoiseInstance->generatePrimedGradient(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 8) {
            noise = this->NoiseInstance->generatePrimedDensity(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 9) {
            noise = this->NoiseInstance->generateBetterGradient(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 10) {
            noise = this->NoiseInstance->generateWavelet(this->pairingFunction, this->noiseType, this->width, this->height);
        } else if (this->noiseType == 11) {
            noise = this->NoiseInstance->generatePhasor(this->pairingFunction, this->noiseType, this->width, this->height);
        } else {
            // TODO: Throw error
        }

        /// FIXME
        noiseVec = noise;

        // Save generated noise
        this->imageInstance->saveBMP(noise, this->saveImageFlag, this->width, this->height, fileNoise);
        //this->imageInstance->saveSVG(noise, this->saveImageFlag, this->width, this->height, fileNoise);

        // Generate prime distribution on polar plot
        int primeDistributionFlag = 0;
        if (primeDistributionFlag == 1) {
            PrimePlot *primePlotInstance;
            //primePlotInstance->generatePrimePlot();
            //primePlotInstance->generateUnitCircle();
            primePlotInstance->generateGradientSVG();
            primePlotInstance->generateGradientSVGCube();
            delete primePlotInstance;
        }

        // Run Fourier & amplitude analysis
        if (this->analysisFlag == 1) {
            printf("\nStarting analysis.\n");
            this->AnalysisInstance->runAnalysis(noise, this->pairingFunction, this->noiseType, this->width, this->height, this->amplitudeAnalysisFlag, this->fourierAnalysisFlag);
            printf("Successfully completed analysis.\n");
        }

        delete imageInstance;
        delete AnalysisInstance;
        delete NoiseInstance;
    }


    /// ================================ GLFW/GLEW CONFIGURATION ================================
    // GLFW Window Generation
    if (!glfwInit()) {
        printf("Error glfwInit.\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //glfwWindowHint(GLFW_SAMPLES, 8);

    // Get primary monitory dimensions
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    // Create window
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Render", monitor, NULL);

    if (!window) {
        printf("Error glfwCreateWindow.\n");
        glfwTerminate();
        return -1;
    }

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("Error glewInit.\n");
        return -1;
    }


    /// ================================= OPENGL CONFIGURATION =================================
    // Check for error
    while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - Setup1] " << err << std::endl;

    glViewport(0, 0, fbWidth, fbHeight);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Allow for z-buffer to properly color closer object over further objects
    glEnable(GL_DEPTH_TEST); /// FIXME
    glDepthFunc(GL_LESS);

    // Allow for seamless cubemap
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // Mipmap requirement
    while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - Setup2a] " << err << std::endl;
    //glEnable(GL_TEXTURE_2D);
    while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - Setup2b] " << err << std::endl;

    //glEnable(GL_MULTISAMPLE);
    //glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

    while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - Setup3] " << err << std::endl;

    /// =============== SHADER COMPILATION/LINKAGE & TEXTURE GENERATION/LINKAGE ===============
    while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - Shader1] " << err << std::endl;
    Shader noiseShader("../res/shaders/core.vert", "../res/shaders/core.frag");
    Shader terrainShader("../res/shaders/terrain.vert", "../res/shaders/terrain.frag");
    Shader skyboxShader("../res/shaders/skybox.vert", "../res/shaders/skybox.frag");
    Shader planetShader("../res/shaders/planet.vert", "../res/shaders/planet.frag");
    while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - Shader2] " << err << std::endl;

    printf("\nStarting texture generation.");

    if (applicationType == 0) {
        this->textures = new GLuint[3];

        /// Noise shader and texture setup
        noiseShader.bind();

        // Generate 8 textures
        glGenTextures(2, this->textures);

        // Activate texture and bind current texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->textures[0]);

        // Load texture from file
        this->textureInstance.generateNoiseTexture(this->textures);

        // Set uniform
        glUniform1i(glGetUniformLocation(noiseShader.Program, "noiseTexture"), 0);
        //glUniform1i(glGetUniformLocation(noiseShader.Program, "normalMap"), 0);

        ///
        // Load normal map texture from file
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->textures[1]);

        this->textureInstance.readNoiseTextureNormalMap(this->textures);
        glUniform1i(glGetUniformLocation(noiseShader.Program, "normalMap"), 1);

        // Load coloured noise texture from file
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, this->textures[2]);

        this->textureInstance.readNoiseTextureColor(this->textures);
        glUniform1i(glGetUniformLocation(noiseShader.Program, "noiseTextureColor"), 2);
        ///

        // Unbind texture and shader
        glBindTexture(GL_TEXTURE_2D, 0);
        noiseShader.unbind();

    } else if (applicationType == 1){
        this->textures = new GLuint[8];

        /// Noise shader and texture setup
        //noiseShader.bind();

        // Generate 8 textures
        /*glGenTextures(8, this->textures);

        // Activate texture and bind current texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->textures[0]);

        // Load texture from file
        this->textureInstance.generateNoiseTexture(this->textures);

        // Set uniform
        glUniform1i(glGetUniformLocation(noiseShader.Program, "noiseTexture"), 0);

        // Unbind texture and shader
        glBindTexture(GL_TEXTURE_2D, 0);*/
        //noiseShader.unbind();

        /// Terrain shaders and textures setup
        printf("\n    Starting terrain texture generation.");
        terrainShader.bind();

        glGenTextures(8, this->textures);

        // Activate texture and bind current texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->textures[0]);

        // Load texture from file
        this->textureInstance.generateNoiseTexture(this->textures);

        // Set uniform
        glUniform1i(glGetUniformLocation(terrainShader.Program, "noiseTexture"), 0);

        // Unbind texture and shader
        glBindTexture(GL_TEXTURE_2D, 0);

        const char* uniformTerrain[6] = {"grass", "rock", "sand", "snow", "water", "lunar"};

        // Earth
        const std::string filenameTerrain[] = {"../res/textures/grass.png", "../res/textures/rock.png",
                                               "../res/textures/sand.png", "../res/textures/snow.png",
                                               "../res/textures/water.png", "../res/textures/8k_mercury.jpg"};

        /*const std::string filenameTerrain[] = {"../res/textures/8k_mercury.jpg", "../res/textures/8k_mercury.jpg",
                                               "../res/textures/8k_mercury.jpg", "../res/textures/snow.png",
                                               "../res/textures/water.png", "../res/textures/2k_earth_daymap.jpg"};*/

        // Lunar
        /*const std::string filenameTerrain[] = {"../res/textures/8k_mercury.jpg", "../res/textures/8k_mercury.jpg",
                                               "../res/textures/8k_mercury.jpg", "../res/textures/8k_mercury.jpg",
                                               "../res/textures/water.png", "../res/textures/8k_mars.jpg"};*/

        // Load terrain textures from file
        for (int i = 0; i < 5; i++) {

            int tempIndex = i + 1;

            // Bind current texture
            glActiveTexture(GL_TEXTURE1 + i);
            glBindTexture(GL_TEXTURE_2D, this->textures[tempIndex]);

            this->textureInstance.generateTerrainTexture(i, filenameTerrain[i]);

            // Link to Shader Uniform
            glUniform1i(glGetUniformLocation(terrainShader.Program, uniformTerrain[i]), tempIndex);

            // Unbind current texture
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        // Unbind current texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Rebind GL_TEXTURE0 and unbind shader
        glActiveTexture(GL_TEXTURE0);
        terrainShader.unbind();

        printf("    Successfully completed terrain texture generation.\n");


        /// Planet shader and texture setup
        // Noise shader and texture setup
        planetShader.bind();

        // Activate texture and bind current texture
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, this->textures[6]);

        this->textureInstance.generateTerrainTexture(5, filenameTerrain[5]);

        // Set uniform
        glUniform1i(glGetUniformLocation(planetShader.Program, "planetTexture"), 6);

        // Unbind texture and shader
        glBindTexture(GL_TEXTURE_2D, 0);
        planetShader.unbind();

        printf("    Successfully completed planet texture generation.\n");


        /// Skybox shader and texture setup

        printf("\n    Starting skybox texture generation.");
        while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - SkyboxTexture1] " << err << std::endl;
        skyboxShader.bind();

        // Load skybox textures
        /*const std::string filenameSkybox[] = {"../res/textures/miramar_ft.png", "../res/textures/miramar_bk.png",
                                              "../res/textures/miramar_dn.png", "../res/textures/miramar_up.png",
                                              "../res/textures/miramar_rt.png", "../res/textures/miramar_lf.png"
        };*/
        const std::string filenameSkybox[] = {"../res/textures/miramar_ft.png", "../res/textures/miramar_bk.png",
                                              "../res/textures/miramar_up.png", "../res/textures/miramar_dn.png",
                                              "../res/textures/miramar_rt.png", "../res/textures/miramar_lf.png"
        };

        /*const std::string filenameSkybox[] = {"../res/textures/space_ft.png", "../res/textures/space_bk.png",
                                              "../res/textures/space_dn.png", "../res/textures/space_up.png",
                                              "../res/textures/space_rt.png", "../res/textures/space_lf.png"
        };*/

        // Bind current texture
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->textures[7]);

        // Load skybox textures from file
        for (unsigned int i = 0; i < 6; i++) {
            // Check for error
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - SkyboxTexture2a_" << i << "] " << err << std::endl;
            this->textureInstance.generateSkyboxTexture(i, filenameSkybox[i]);
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - SkyboxTexture2b_" << i << "] " << err << std::endl;

        }


        // Set texture filtering
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        /*glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);*/
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glUniform1i(glGetUniformLocation(skyboxShader.Program, "skybox"), 7);


        // Unbind texture and shader
        //glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        skyboxShader.unbind();


        printf("    Successfully completed skybox texture generation.\n");
    }

    // Check for error
    while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - SkyboxTexture3] " << err << std::endl;


    /// =============================== GENERATE MESH/UPDATE INITIAL VARIABLES ===============================
    if (this->applicationType == 0) {               // Wavefront (OBJ object)
        while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Mesh1] " << err << std::endl;
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        this->meshInstance.generateMeshFromFile();
        //this->meshInstance.generateMeshFromNoise(this->width, this->height, noiseVec); /// FIXME

        this->translationStart = glm::vec3(0.000f, 0.000f, 0.000f);
        this->rotationStart = glm::vec3(0.000f, 1.000f, 0.000f);
        //this->scaleStart = glm::vec3(0.075f, 0.075f, 0.075f);
        this->scaleStart = glm::vec3(4.0f, 4.0f, 4.0f);/// FIXME

        // Camera initial location
        this->cameraPosition   = glm::vec3(0.0f, 0.0f,  10.0f);
        this->cameraLookatOrigin   = glm::vec3(0.0f, 0.0f,  0.0f);
        this->cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

        // Initial factors
        this->fovFactor = 90.0f;
        this->rotateFactor = 0.0f;
        this->scaleFactor = 1.0f;

        // Setup buffers
        Renderer::setupBuffersMesh();
        while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Mesh2] " << err << std::endl;

    } else if (this->applicationType == 1) {        // Procedural Landscape
        while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App2_Mesh1] " << err << std::endl;
        this->meshInstance.generateMeshFromNoise(this->width, this->height, noiseVec); /// FIXME
        this->meshInstance.generateSkybox();
        this->meshInstance.generatePlanet();

        /*/// TODO: move
        this->translationStart = glm::vec3(4.615f, 0.000f, 0.000f);
        this->rotationStart = glm::vec3(0.035f, 0.000f, 0.000f);
        this->scaleStart = glm::vec3(2.000f, 2.000f, 2.000f);

        // Camera initial location
        this->cameraPosition   = glm::vec3(0.0f, 1.0f,  20.0f);
        this->cameraLookatOrigin   = glm::vec3(0.0f, 0.0f,  0.0f);
        this->cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

        // Initial factors
        this->fovFactor = 86.0f;
        this->rotateFactor = 20.769f;
        this->scaleFactor = 2.0f;*/

        // Camera initial location
        this->cameraPosition   = glm::vec3(0.0f, 0.0f,  1.0f);
        //this->cameraPosition   = glm::vec3(0.0f, 0.0f, 0.5f);
        this->cameraLookatOrigin   = glm::vec3(0.0f, 0.0f,  0.0f);
        this->cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

        // Initial factors
        this->fovFactor = 90.0f;
        this->rotateFactor = 0.0f;
        this->scaleFactor = 1.0f;

        // Setup buffers
        Renderer::setupBuffersMesh();
        Renderer::setupBuffersMeshSkybox();
        Renderer::setupBuffersMeshPlanet();
        while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App2_Mesh2] " << err << std::endl;


    } else {
        // TODO: throw error
    }

    /*
    //glEnable(GL_SCISSOR_TEST);
    //glScissor(0,0, fbWidth * .75, fbHeight *.75);
    */

    /// =============================== IMGUI SETUP ===============================
    // ImGui initialization
    const char* glsl_version = "#version 330";
    bool toolActiveFlag = true;
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // ImGui background and texture starting colours
    glm::vec4 clearColor  = glm::vec4(1.000f, 1.000f, 1.000f, 1.000f);
    glm::vec4 texColor    = glm::vec4(1.000f, 1.000f, 1.000f, 1.000f);

    /// =============================== CAMERA SETUP ===============================
    // Initialize camera
    Camera camera = Camera(fbWidth, fbHeight, this->cameraPosition, this->cameraUp, -90.f, 0.0f);

    /// ================================== RENDER ==================================
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        //glfwPollEvents();

        // ImGui frame initialization
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - Render1] " << err << std::endl;
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (this->applicationType == 0) {

            // Activate shader
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render1] " << err << std::endl;
            noiseShader.bind();

            // Bind texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->textures[0]);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, this->textures[1]);///
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, this->textures[2]);///

            // Projection
            int fbWidthNew, fbHeightNew;
            glfwGetFramebufferSize(window, &fbWidthNew, &fbHeightNew);
            camera.updateCameraZoom(this->fovFactor);
            camera.updateProjection(fbWidthNew, fbHeightNew);
            glm::mat4 projection = camera.getProjection();

            // View
            camera.updateCameraPosition(this->cameraPosition);
            camera.updateCameraDirection(this->cameraLookatOrigin);
            glm::mat4 view = camera.getView();

            // Model
            camera.updateModel(this->translationStart, this->rotationStart, this->scaleStart * this->scaleFactor, this->rotateFactor);
            glm::mat4 model = glm::mat4(1.0f);
            model = camera.getModel();

            // Aggregate MVP matrices into single transform matrix
            glm::mat4 transform = projection * view * model;

            // Get matrix's uniform location and set matrix
            GLint transformLocation = glGetUniformLocation(noiseShader.Program, "transform");
            glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

            ///
            // Get matrix's uniform location and set matrix
            GLint modelLocation = glGetUniformLocation(noiseShader.Program, "model");
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

            // Get matrix's uniform location and set matrix
            GLint viewLocation = glGetUniformLocation(noiseShader.Program, "view");
            glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

            // Get matrix's uniform location and set matrix
            GLint projectionLocation = glGetUniformLocation(noiseShader.Program, "projection");
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

            // Get matrix's uniform location and set matrix
            //GLint viewPosLocation = glGetUniformLocation(noiseShader.Program, "viewPos");
            //glUniformMatrix4fv(viewPosLocation, 1, GL_FALSE, glm::value_ptr(this->cameraPosition));
            GLint viewPosLocation = glGetUniformLocation(terrainShader.Program, "viewPos");
            glUniform3f(viewPosLocation, this->cameraPosition.x, this->cameraPosition.y, this->cameraPosition.z);
            ///

            // Draw container
            glBindVertexArray(this->VAO);
            glDrawElements(GL_TRIANGLES, this->meshInstance.numIndices, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render2] " << err << std::endl;

        } else if (this->applicationType == 1) {

            // Projection
            int fbWidthNew, fbHeightNew;
            glfwGetFramebufferSize(window, &fbWidthNew, &fbHeightNew);
            camera.updateCameraZoom(this->fovFactor);
            camera.updateProjection(fbWidthNew, fbHeightNew);
            glm::mat4 projection = camera.getProjection();

            camera.updateCameraPosition(this->cameraPosition);
            camera.updateCameraDirection(this->cameraLookatOrigin);

            /// Terrain
            // Activate shader
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Terrain1] " << err << std::endl;
            terrainShader.bind();

            // Bind noise texture (heightmap)
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->textures[0]);

            // Bind Grass
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, this->textures[1]);

            // Bind Rock
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, this->textures[2]);

            // Bind Sand
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, this->textures[3]);

            // Bind Snow
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, this->textures[4]);

            // Bind Water
            glActiveTexture(GL_TEXTURE5);
            glBindTexture(GL_TEXTURE_2D, this->textures[5]);

            // Bind Lunar
            /*glActiveTexture(GL_TEXTURE6);
            glBindTexture(GL_TEXTURE_2D, this->textures[6]);*/

            // View
            camera.updateCameraPosition(this->cameraPosition);
            camera.updateCameraDirection(this->cameraLookatOrigin);
            glm::mat4 view = camera.getView();

            // Model
            camera.updateModel(this->translationStart, this->rotationStart, this->scaleStart * this->scaleFactor, this->rotateFactor);
            glm::mat4 model = glm::mat4(1.0f);
            model = camera.getModel();

            // Aggregate MVP matrices into single transform matrix
            glm::mat4 transform = projection * view * model;

            /*// Projection
            int fbWidthNew, fbHeightNew;
            glfwGetFramebufferSize(window, &fbWidthNew, &fbHeightNew);
            camera.updateCameraZoom(this->fovFactor);
            camera.updateProjection(fbWidthNew, fbHeightNew);
            glm::mat4 projection = camera.getProjection();

            // View
            camera.updateCameraPosition(this->cameraPosition);
            camera.updateCameraDirection(this->cameraLookatOrigin);
            glm::mat4 view = camera.getView();

            // Model
            camera.updateModel(this->translationStart, this->rotationStart, this->scaleStart * this->scaleFactor, this->rotateFactor);
            glm::mat4 model = glm::mat4(1.0f);
            model = camera.getModel();

            // Aggregate MVP matrices into single transform matrix
            glm::mat4 transform = projection * view * model;*/

            // Get matrix's uniform location and set matrix
            GLint transformLocation = glGetUniformLocation(terrainShader.Program, "transform");
            glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

            // Set updated viewPos
            GLint viewPosLocation = glGetUniformLocation(terrainShader.Program, "viewPos");
            glUniform3f(viewPosLocation, this->cameraPosition.x, this->cameraPosition.y, this->cameraPosition.z);

            // Set updated wave motion
            if (this->waveMotion > 1.0f) {
                this->waveMotion = 0.0f;
            } else {
                this->waveMotion += 0.0001f;
            }

            GLint waveMotionLocation = glGetUniformLocation(terrainShader.Program, "waveMotion");
            glUniform1f(waveMotionLocation, this->waveMotion);

            // Draw container
            glBindVertexArray(this->VAO);
            glDrawElements(GL_TRIANGLES, this->meshInstance.numIndices, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            terrainShader.unbind();
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Terrain2] " << err << std::endl;

            /// Planet
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Planet1] " << err << std::endl;
            planetShader.bind();
            glActiveTexture(GL_TEXTURE6);
            glBindTexture(GL_TEXTURE_2D, this->textures[6]);

            // View
            view = camera.getView();

            // Model
            //float scaleOffset = 0.1f;
            //glm::vec3 translationOffset = glm::vec3(-1.5f, 2.5f, 1.0f);
            camera.updateModel(this->translationStart + this->planetLocation, this->rotationStart, this->planetScaleVec * this->planetScale, this->rotateFactor);
            model = glm::mat4(1.0f);
            model = camera.getModel();

            // Aggregate MVP matrices into single transform matrix
            transform = projection * view * model;

            // Get matrix's uniform location and set matrix
            transformLocation = glGetUniformLocation(planetShader.Program, "transform");
            glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

            // Draw container
            glBindVertexArray(this->plVAO);
            glDrawElements(GL_TRIANGLES, this->meshInstance.numIndicesPlanet, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            planetShader.unbind();
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Planet2] " << err << std::endl;

            /// Skybox
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox1] " << err << std::endl;

            // Activate shader
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox2] " << err << std::endl;
            GLint OldCullFaceMode;
            glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
            glCullFace(GL_FRONT);
            glDepthFunc(GL_LEQUAL);
            //glEnable(GL_DEPTH_TEST);
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox3] " << err << std::endl;
            skyboxShader.bind();
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox4] " << err << std::endl;
            //glEnable(GL_TEXTURE_2D);
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox5] " << err << std::endl;

            // Bind skybox texture
            glActiveTexture(GL_TEXTURE7);
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox6] " << err << std::endl;
            glBindTexture(GL_TEXTURE_CUBE_MAP, this->textures[7]);
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox7] " << err << std::endl;

            // Bind VAO
            glBindVertexArray(this->sbVAO);
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox8] " << err << std::endl;

            ///
            camera.updateCameraZoom(this->fovFactor);
            camera.updateProjection(fbWidthNew, fbHeightNew);
            projection = camera.getProjection();

            camera.updateCameraPosition(this->cameraPosition);
            camera.updateCameraDirection(this->cameraLookatOrigin);
            ///

            // Calculate transform
            glm::mat4 modelS = glm::mat4(1.0f);
            //modelS = glm::translate(modelS, glm::vec3(-0.5f, 0.0f, 0.0f));
            //modelS = glm::translate(modelS, glm::vec3(this->cameraPosition.x / 2.0f, this->cameraPosition.y / 2.0f, this->cameraPosition.z / 2.0f));
            //modelS = glm::translate(modelS, glm::vec3(this->cameraPosition.x, this->cameraPosition.y, -this->cameraPosition.z));
            //modelS = glm::rotate(modelS, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            //modelS = glm::scale(modelS, glm::vec3(5.0f, 5.0f, 5.0f));

            // Calculate view
            glm::mat4 viewS = glm::mat4(1.0f);
            viewS = glm::mat4(glm::mat3(camera.getView()));

            //viewS = viewS * modelS;
            //viewS = viewS * modelS * projection;
            //viewS = projection * viewS * modelS;
            //view = glm::mat4(glm::mat3(camera.getView()));

            GLint viewSB = glGetUniformLocation(skyboxShader.Program, "viewSB");
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox9] " << err << std::endl;
            glUniformMatrix4fv(viewSB, 1, GL_FALSE, glm::value_ptr(viewS));
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox10] " << err << std::endl;

            GLint projectionSB = glGetUniformLocation(skyboxShader.Program, "projectionSB");
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox11] " << err << std::endl;
            glUniformMatrix4fv(projectionSB, 1, GL_FALSE, glm::value_ptr(projection));
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox12] " << err << std::endl;

            // Draw
            //glUniform1i(glGetUniformLocation(skyboxShader.Program, "skybox"), 7);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox13] " << err << std::endl;
            glBindVertexArray(0);
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox14] " << err << std::endl;
            skyboxShader.unbind();
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox15] " << err << std::endl;
            //glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            glCullFace(OldCullFaceMode);

            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox15] " << err << std::endl;
            while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_Skybox16] " << err << std::endl;
        } else {
            // TODO: throw error
        }

        // Main Menu Bar
        if (ImGui::BeginMainMenuBar()) {

            if (ImGui::BeginMenu("File")) {
                //if (ImGui::MenuItem("Open", "Ctrl+O")) {}
                if (ImGui::BeginMenu("Save As")) {
                    if (ImGui::MenuItem("BMP", "Ctrl+S+B")) {
                        std::string filenameBMP = "../Output/Applications/" + fileApp + ".bmp";
                        saveBMP(filenameBMP, window);
                    }

                    if (ImGui::MenuItem("PNG", "Ctrl+S+P")) {
                        std::string filenamePNG = "../Output/Applications/" + fileApp + ".png";
                        savePNG(filenamePNG, window);
                    }

                    ImGui::EndMenu();
                }

                // Close "Options" menu
                if (ImGui::MenuItem("Close Options Menu", "Ctrl+~")) {
                    this->ImguiActiveFlag = false;
                }

                // Close Program
                if (ImGui::MenuItem("Close Application", "Ctrl+Q")) {
                    glfwSetWindowShouldClose(window, 1);
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        // ImGui screen content
        if (this->ImguiActiveFlag) {
            {
                // Show demo window for ImGui reference
                //ImGui::ShowDemoWindow();

                ImGui::Begin("Options", &toolActiveFlag, ImGuiWindowFlags_MenuBar);

                // Selected parameters
                ImGui::Text("%s", this->imguiApplicationType);
                ImGui::Text("%s", this->imguiNoiseType);
                ImGui::Text("%s", this->imguiPairingFunction);
                ImGui::NewLine();

                // Background colour
                //ImGui::ColorEdit4("Clear Color", &clearColor[0], 0);

                // Texture colour
                //ImGui::SliderFloat4("Texture Color", &texColor[0], 0.000f, 1.000f);

                // Translation
                ImGui::Text("Translation: ");
                ImGui::SliderFloat("Translate Object X", &this->translationStart[0], -100.000f, 100.000f);
                ImGui::SliderFloat("Translate Object Y", &this->translationStart[1], -100.000f, 100.000f);
                ImGui::SliderFloat("Translate Object Z", &this->translationStart[2], -100.000f, 100.000f);

                // Rotation
                ImGui::Text("Rotation: ");
                ImGui::SliderFloat("Degrees to Rotate", &this->rotateFactor, 0.000f, 360.000f);
                ImGui::SliderFloat("Rotate Object X", &this->rotationStart[0], 0.000f, 1.000f);
                ImGui::SliderFloat("Rotate Object Y", &this->rotationStart[1], 0.000f, 1.000f);
                ImGui::SliderFloat("Rotate Object Z", &this->rotationStart[2], 0.000f, 1.000f);

                // Scale
                ImGui::Text("Scale: ");
                ImGui::SliderFloat("Scale Object X", &this->scaleStart[0], 0.000f, 2.000f);
                ImGui::SliderFloat("Scale Object Y", &this->scaleStart[1], 0.000f, 2.000f);
                ImGui::SliderFloat("Scale Object Z", &this->scaleStart[2], 0.000f, 2.000f);
                ImGui::SliderFloat("Scale All", &this->scaleFactor, 0.000f, 2.000f);
                ImGui::NewLine();

                // Camera Position
                ImGui::Text("Camera Position: ");
                ImGui::SliderFloat("Camera Position X", &this->cameraPosition[0], -50.000f, 50.000f);
                ImGui::SliderFloat("Camera Position Y", &this->cameraPosition[1], -50.000f, 50.000f);
                ImGui::SliderFloat("Camera Position Z", &this->cameraPosition[2], -50.000f, 50.000f);

                // Camera Viewing Direction
                ImGui::Text("Camera Viewing Direction: ");
                ImGui::SliderFloat("Camera Direction X", &this->cameraLookatOrigin[0], -180.000f, 180.000f);
                ImGui::SliderFloat("Camera Direction Y", &this->cameraLookatOrigin[1], -180.000f, 180.000f);

                // Field of View
                ImGui::Text("Field of View: ");
                ImGui::SliderFloat("Field of View", &this->fovFactor, 1.000f, 180.000f);
                ImGui::NewLine();

                // Planet Position
                ImGui::Text("Planet Location: ");
                ImGui::SliderFloat("Planet Position X", &this->planetLocation[0], -50.000f, 50.000f);
                ImGui::SliderFloat("Planet Position Y", &this->planetLocation[1], -50.000f, 50.000f);
                ImGui::SliderFloat("Planet Position Z", &this->planetLocation[2], -50.000f, 50.000f);
                ImGui::SliderFloat("Planet Scale", &this->planetScale, 0.000f, 2.000f);

                // Framerate
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                            ImGui::GetIO().Framerate);
                ImGui::End();
            }
        }

        // Rendering Editing Window
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_2] " << err << std::endl;
        glfwSwapBuffers(window);
        while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_3] " << err << std::endl;
        glfwPollEvents();
        while((err = glGetError()) != GL_NO_ERROR) std::cerr << "[OPENGL ERROR - App1_Render_4] " << err << std::endl;
    }

    // Shutdown ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Save as BMP
    std::string filenameBMP = "../Output/Applications/" + fileApp + ".bmp";
    saveBMP(filenameBMP, window);

    // Clean up
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
    glDeleteVertexArrays(1, &this->sbVAO);
    glDeleteBuffers(1, &this->sbVBO);
    glDeleteBuffers(1, &this->sbEBO);
    glDeleteVertexArrays(1, &this->plVAO);
    glDeleteBuffers(1, &this->plVBO);
    glDeleteBuffers(1, &this->plEBO);

    glfwTerminate();
    return 0;
}


