/**
 * Camera.h
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of a first person camera.
 */

#include <iostream>
#include <GL/glew.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

class Camera {
public:

    Camera();
    Camera(GLfloat screenWidth, GLfloat screenHeight, glm::vec3 cameraPosition, glm::vec3 cameraUp, GLfloat yaw, GLfloat pitch);
    ~Camera();

    // Update MVP matrices
    void updateModel(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale, GLfloat rotateFactor);
    void updateView();
    void updateProjection(int width, int height);

    // Getter for MVP matrices
    glm::mat4 getModel();
    glm::mat4 getView();
    glm::mat4 getProjection();

    // Adjust camera position
    void updateCameraPosition(glm::vec3 newPosition);

    // Adjust camera viewing direction
    void updateCameraDirection(glm::vec3 newDirection);

    // Adjust camera fov
    void updateCameraZoom(GLfloat newFOV);

private:

    // MVP Matrices
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    // Model matrix components
    GLfloat rotateFactor;
    glm::vec3 translationStart;
    glm::vec3 rotationStart;
    glm::vec3 scaleStart;

    // Camera
    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::vec3 lastCameraDirection;

    // Movement attributes
    GLfloat speed;
    GLfloat fov;

    // Tilt
    GLfloat roll;       // TODO: implement
    GLfloat pitch;
    GLfloat yaw;
};