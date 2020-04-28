/**
 * Texture.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of OpenGL-based texture generation.
 */

#include <icg_common.h>
#include "Texture.h"

Texture::Texture() {}

Texture::~Texture() {}

/*
 * Sets up coordinates for square to use in buffers.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::setupSquareCoordinates() {
    GLfloat vertices[] = {
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };

    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    numIndices = 6;
    pVertices.assign(std::begin(vertices), std::end(vertices));
    pIndices.assign(std::begin(indices), std::end(indices));

    return 0;
}

/*
 * Sets up coordinates for a cube to use in buffers.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::setupCubeCoordinates() {
    GLfloat vertices[] = {
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.000059f, 1.0f-0.000004f,
            -1.0f,-1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.000103f, 1.0f-0.336048f,
            -1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            1.0f, 1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       1.000023f, 1.0f-0.000013f,
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            -1.0f, 1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.999958f, 1.0f-0.336064f,
            1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.336024f, 1.0f-0.671877f,
            1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.667969f, 1.0f-0.671889f,
            1.0f, 1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       1.000023f, 1.0f-0.000013f,
            1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.668104f, 1.0f-0.000013f,
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.000059f, 1.0f-0.000004f,
            -1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            -1.0f, 1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.336098f, 1.0f-0.000071f,
            1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            -1.0f,-1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            -1.0f,-1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.336024f, 1.0f-0.671877f,
            -1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       1.000004f, 1.0f-0.671847f,
            -1.0f,-1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.999958f, 1.0f-0.336064f,
            1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.668104f, 1.0f-0.000013f,
            1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            1.0f, 1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f,
            1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.668104f, 1.0f-0.000013f,
            1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.336098f, 1.0f-0.000071f,
            1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.000103f, 1.0f-0.336048f,
            1.0f, 1.0f,-1.0f,       1.0f, 0.0f, 0.0f,       0.000004f, 1.0f-0.671870f,
            -1.0f, 1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.336024f, 1.0f-0.671877f,
            1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.000103f, 1.0f-0.336048f,
            -1.0f, 1.0f,-1.0f,      1.0f, 0.0f, 0.0f,       0.336024f, 1.0f-0.671877f,
            -1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       0.335973f, 1.0f-0.335903f,
            1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.667969f, 1.0f-0.671889f,
            -1.0f, 1.0f, 1.0f,      1.0f, 0.0f, 0.0f,       1.000004f, 1.0f-0.671847f,
            1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f,       0.667979f, 1.0f-0.335851f
    };

    GLuint indices[36];
    for (int i = 0; i < 36; ++i) {
        indices[i] = i;
    }

    numIndices = 36;
    pVertices.assign(std::begin(vertices), std::end(vertices));
    pIndices.assign(std::begin(indices), std::end(indices));

    return 0;
}

/*
 * Sets up coordinates for given mesh for use in buffers.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::setupMeshCoordinates(std::vector<Mesh::s_Mesh> meshes) {

    // Read vertices and indices into arrays
    std::vector<Mesh::Vertex> mVertices = meshes[0].vertices;
    std::vector<unsigned int> mIndices = meshes[0].indices;

    float minX = 999999.0f;
    float minY = 999999.0f;
    float minZ = 999999.0f;
    float maxX = -999999.0f;
    float maxY = -999999.0f;
    float maxZ = -999999.0f;

    //GLfloat vertices[mVertices.size() * 8];
    for (int i = 0; i < mVertices.size(); ++i) {
        pVertices.push_back(mVertices[i].position.x);
        pVertices.push_back(mVertices[i].position.y);
        pVertices.push_back(mVertices[i].position.z);

        pVertices.push_back(mVertices[i].normal.x);
        pVertices.push_back(mVertices[i].normal.y);
        pVertices.push_back(mVertices[i].normal.z);

        pVertices.push_back(mVertices[i].uv.x);
        pVertices.push_back(mVertices[i].uv.y);

        maxX = (mVertices[i].position.x > maxX) ? mVertices[i].position.x : maxX;
        minX = (mVertices[i].position.x < minX) ? mVertices[i].position.x : minX;
        maxY = (mVertices[i].position.y > maxY) ? mVertices[i].position.y : maxY;
        minY = (mVertices[i].position.y < minY) ? mVertices[i].position.y : minY;
        maxZ = (mVertices[i].position.z > maxZ) ? mVertices[i].position.z : maxZ;
        minZ = (mVertices[i].position.z < minZ) ? mVertices[i].position.z : minZ;
    }

    xRange = maxX - minX;
    yRange = maxY - minY;
    zRange = maxZ - minZ;
    xMid = xRange + minX;
    yMid = yRange + minY;
    zMid = zRange + minZ;

    numIndices = mIndices.size();
    pIndices = mIndices;

    return 0;
}

/*
 * Sets up buffers depending on given inputs.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::setupBuffers(std::vector<Mesh::s_Mesh> meshes) {

    // Setup coordinates
    //setupSquareCoordinates();
    //setupCubeCoordinates();
    setupMeshCoordinates(meshes);

    GLfloat vertices[pVertices.size()];
    std::copy(pVertices.begin(), pVertices.end(), vertices);

    GLuint indices[pIndices.size()];
    std::copy(pIndices.begin(), pIndices.end(), indices);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
 * Reads texture image from file.
 *
 * Returns:
 *      0 if succesfully completed. TODO: return -1 if failed
 */
int Texture::readTexture() {

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );

    // Set our texture parameters and texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Define filename of texture to read
    std::string filename = "../Output/temp/noise_output.bmp";

    // TODO: ADD FORMAT FROM NOISE VECTOR
    // Create texture and generate mipmaps
    unsigned char* image = stbi_load(filename.c_str(), &texWidth, &texHeight, 0, 4);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image);

    glBindTexture(GL_TEXTURE_2D, 0);

    return 0;
}

/*
 * Saves image as PNG.
 *
 * Returns:
 *      0 otherwise. TODO: Return -1 if false
 */
int Texture::savePNG(std::string filename, GLFWwindow* window) {

    printf("\nAttempting to write framebuffer to PNG.\n");

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * width;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    GLsizei bufferSize = stride * height;

    std::vector<char> buffer(bufferSize);

    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

    stbi_flip_vertically_on_write(true);
    stbi_write_png(filename.c_str(), width, height, nrChannels, buffer.data(), stride);

    printf("Successfully wrote framebuffer to PNG.\n");

    return 0;
}

/*
 * Saves image as BMP.
 *
 * Returns:
 *      0 otherwise. TODO: Return -1 if false
 */
int Texture::saveBMP(std::string filename, GLFWwindow* window) {

    printf("\nAttempting to write framebuffer to BMP.\n");

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * width;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    GLsizei bufferSize = stride * height;

    std::vector<char> buffer(bufferSize);

    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

    stbi_flip_vertically_on_write(true);
    stbi_write_bmp(filename.c_str(), width, height, nrChannels, buffer.data());

    printf("Successfully wrote framebuffer to BMP.\n");

    return 0;
}

/*
 * Generates window and drives texture application.
 *
 * Returns:
 *      -1 if error occurs, 0 otherwise.
 */
int Texture::generateTexture(std::vector<Noise::Point> noise, std::vector<Mesh::s_Mesh> meshes, std::string file) {

    // GLFW Window Generation
    if (!glfwInit()) {
        printf("Error glfwInit.\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window;
    window = glfwCreateWindow(500, 500, "Vase Model", nullptr, nullptr);
    if (!window) {
        printf("Error glfwCreateWindow.\n");
        glfwTerminate();
        return -1;
    }

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("Error glewInit.\n");
        return -1;
    }

    glViewport(0, 0, screenWidth, screenHeight);

    // Allow for alpha channel to be supported
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Allow for z-buffer to properly color closer object over further objects
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Create and compile shaders
    Shader ourShader("../res/shaders/core.vert", "../res/shaders/core.frag");

    // Setup buffers
    Texture::setupBuffers(meshes);

    // Read texture from file
    Texture::readTexture();

    // Render
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        glfwPollEvents();

        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        ourShader.Use();

        // Activate texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(ourShader.Program, "marbleTexture"), 0);

        // Projection
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), 750.0f / 750.0f, 0.1f, 100.0f);

        // View
        glm::mat4 view = glm::lookAt(glm::vec3( 0.0f,1.0f,20.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));

        // Model translation
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

        // Model rotation (off)
        //model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::rotate(model, -200.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        // Model scale
        model = glm::scale(model, glm::vec3(0.075f, 0.075f, 0.075f));

        glm::mat4 transform = projection * view * model;

        // Get matrix's uniform location and set matrix
        GLint transformLocation = glGetUniformLocation(ourShader.Program, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

        // Draw container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    // Save as BMP
    //std::string filenameBMP = "../Output/Applications/Marble_Perlin_Cantor_Vase.bmp";
    std::string filenameBMP = "../Output/Applications/" + file + ".bmp";
    saveBMP(filenameBMP, window);

    // Save as PNG
    //std::string filenamePNG = "../Output/Applications/Marble_Perlin_Cantor_Vase.png";
    //savePNG(filenamePNG, window);

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}


