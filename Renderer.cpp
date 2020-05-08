/**
 * Renderer.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of GLFW & OpenGL-based rendering.
 */

#include "Renderer.h"

Renderer::Renderer() {

    this->translationStart = glm::vec3(0.000f, 0.000f, 0.000f);
    this->rotationStart = glm::vec3(1.000f, 0.000f, 0.000f);
    this->scaleStart = glm::vec3(0.075f, 0.075f, 0.075f);

    this->cameraPosition   = glm::vec3(0.0f, 1.0f,  20.0f);
    this->cameraLookatOrigin   = glm::vec3(0.0f, 0.0f,  0.0f);
    this->cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    this->fovFactor = 90.0f;
    this->rotateFactor = 0.0f;
    this->scaleFactor = 1.0f;

    this->width = 1000;
    this->height = 1000;
    this->noiseType = 0;
    this->pairingFunction = 1;
    this->saveImageFlag = 1;
    this->applicationType = 0;
    this->analysisFlag = 1;
    this->amplitudeAnalysisFlag = 0;
    this->fourierAnalysisFlag = 1;

    this->ImguiActiveFlag = true;

    updateImguiText();
}

Renderer::Renderer(int width, int height, int noiseType, int pairingFunction, int saveImageFlag,
                   int applicationType, int analysisFlag, int amplitudeAnalysisFlag, int fourierAnalysisFlag) {

    this->translationStart = glm::vec3(0.000f, 0.000f, 0.000f);
    this->rotationStart = glm::vec3(0.000f, 1.000f, 0.000f);
    this->scaleStart = glm::vec3(0.075f, 0.075f, 0.075f);

    this->cameraPosition   = glm::vec3(0.0f, 1.0f,  20.0f);
    this->cameraLookatOrigin   = glm::vec3(0.0f, 0.0f,  0.0f);
    this->cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    this->fovFactor = 90.0f;
    this->rotateFactor = 0.0f;
    this->scaleFactor = 1.0f;

    this->width = width;
    this->height = height;
    this->noiseType = noiseType;
    this->pairingFunction = pairingFunction;
    this->saveImageFlag = saveImageFlag;
    this->applicationType = applicationType;
    this->analysisFlag = analysisFlag;
    this->amplitudeAnalysisFlag = amplitudeAnalysisFlag;
    this->fourierAnalysisFlag = fourierAnalysisFlag;

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
    } else {
        // TODO: Throw error
    }

    if (filenameType == 0) {

        // Noise type
        if (this->noiseType == 0) {
            title = "Perlin_Noise_" + title;
        } else if (this->noiseType == 1) {
            title = "Gabor_Noise_" + title;
        } else if (this->noiseType == 2) {
            title = "Marble_Noise_" + title;
        } else if (this->noiseType == 3) {
            title = "Worley_Noise_" + title;
        } else if (this->noiseType == 4) {
            title = "Curl_Noise_" + title;
        } else {
            // TODO: Throw error
        }
    } else if (filenameType == 1) {

        // Noise type
        if (this->noiseType == 0) {
            title = "Perlin_" + title;
        } else if (this->noiseType == 1) {
            title = "Gabor_" + title;
        } else if (this->noiseType == 2) {
            title = "Marble_" + title;
        } else if (this->noiseType == 3) {
            title = "Worley_" + title;
        }else if (this->noiseType == 4) {
            title = "Curl_" + title;
        }else {
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
 * Generate noise.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Renderer::noiseHelper() {
    if (this->noiseType == 0) {
        this->noise = this->NoiseInstance.generatePerlin(this->pairingFunction, this->noiseType, this->width, this->height);
    } else if (this->noiseType == 1) {
        this->noise = this->NoiseInstance.generateGabor(this->pairingFunction, this->noiseType, this->width, this->height);
    } else if (this->noiseType == 2) {
        this->noise = this->NoiseInstance.generateMarble(this->pairingFunction, this->noiseType, this->width, this->height);
    } else if (this->noiseType == 3) {
        this->noise = this->NoiseInstance.generateWorley(this->pairingFunction, this->noiseType, this->width, this->height);
    } else if (this->noiseType == 4) {
        this->noise = this->NoiseInstance.generateCurl(this->pairingFunction, this->noiseType, this->width, this->height);
    } else {
        // TODO: Throw error
    }

    return 0;
}

/*
 * Sets up buffers depending on given inputs.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Renderer::setupBuffers() {

    GLfloat vertices[this->meshInstance.pVertices.size()];
    std::copy(this->meshInstance.pVertices.begin(), this->meshInstance.pVertices.end(), vertices);

    GLuint indices[this->meshInstance.pIndices.size()];
    std::copy(this->meshInstance.pIndices.begin(), this->meshInstance.pIndices.end(), indices);

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0 );
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture Coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

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
        imguiPairingFunction = "Pairing Function: RosenbergStrong";
    } else {
        // TODO: Throw error
    }

    // Noise type
    if (this->noiseType == 0) {
        imguiNoiseType = "Noise Type: Perlin";
    } else if (this->noiseType == 1) {
        imguiNoiseType = "Noise Type: Gabor";
    } else if (this->noiseType == 2) {
        imguiNoiseType = "Noise Type: Marble";
    } else if (this->noiseType == 3) {
        imguiNoiseType = "Noise Type: Worley";
    } else if (this->noiseType == 4) {
        imguiNoiseType = "Noise Type: Curl";
    } else {
        // TODO: Throw error
    }

    // Application type
    if (this->applicationType == 0) {
        imguiApplicationType = "Application: Vase";
    } else if (this->applicationType == 1) {
        imguiApplicationType = "Application: ProceduralLandscape";
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

    /**
     * Note:    The below 5 function calls need to be moved into the rendering loop so that the user can dynamically
     *          generate noise, load meshes, run analysis, save images and render such applications.
     */

    // Generate noise
    Renderer::noiseHelper();

    // Generate title
    std::string fileNoise = Renderer::generateFilenames(0);
    std::string fileApp = Renderer::generateFilenames(1);

    // Save generated noise
    this->imageInstance.saveBMP(this->noise, this->saveImageFlag, this->width, this->height, fileNoise);

    // Generate mesh
    this->meshes = this->meshInstance.generateMesh();

    // Run analysis
    if (this->analysisFlag == 1) {
        printf("\nStarting analysis.\n");
        this->AnalysisInstance.runAnalysis(this->noise, this->pairingFunction, this->noiseType, this->width, this->height, this->amplitudeAnalysisFlag, this->fourierAnalysisFlag);
        printf("Successfully completed analysis.\n");
    }


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

    // Get primary monitory dimensions
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    // Create window
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);

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

    glViewport(0, 0, fbWidth, fbHeight);

    // Allow for alpha channel to be supported
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Allow for z-buffer to properly color closer object over further objects
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Create and compile shaders
    Shader ourShader("../res/shaders/core.vert", "../res/shaders/core.frag");

    // Setup buffers
    Renderer::setupBuffers();

    // Generate texture from file
    this->textureInstance.generateTexture();

    //glEnable(GL_SCISSOR_TEST); ///
    //glScissor(0,0, fbWidth * .75, fbHeight *.75);

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

    // Initialize camera
    Camera camera = Camera(fbWidth, fbHeight, this->cameraPosition, this->cameraUp, -90.f, 0.0f);

    // Render
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        glfwPollEvents();

        // ImGui frame initialization
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        ourShader.Use();

        // Activate texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->textureInstance.texture);
        glUniform1i(glGetUniformLocation(ourShader.Program, "marbleTexture"), 0);

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
        GLint transformLocation = glGetUniformLocation(ourShader.Program, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

        // Draw container
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, this->meshInstance.numIndices, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

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

                // Framerate
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                            ImGui::GetIO().Framerate);
                ImGui::End();
            }
        }

        // Rendering Editing Window
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
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

    glfwTerminate();
    return 0;
}


