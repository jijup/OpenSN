/**
 * Camera.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of a first person camera.
 */

#include "Camera.h"

/*
 * Default Constructor.
 */
Camera::Camera() {
    // Set initial camera position and world orientation
    this->cameraPosition = glm::vec3(0.0f, 1.0f,  20.0f);
    this->cameraFront = glm::vec3(0.0f, -1.0f, -20.0f);
    this->lastCameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

    // Set initial tilt of camera
    this->yaw = -90.0f;
    this->pitch = 0.0f;

    // Set front, right and up vectors
    Camera::updateView();

    // Set initial model location
    this->rotateFactor = 0.0f;
    this->translationStart = glm::vec3(0.000f, 0.000f, 0.000f);
    this->rotationStart = glm::vec3(1.000f, 0.000f, 0.000f);
    this->scaleStart = glm::vec3(0.075f, 0.075f, 0.075f);

    // Set initial model matrix
    this->model = glm::mat4(1.0f);
    Camera::updateModel(this->translationStart, this->rotationStart, this->scaleStart, rotateFactor);

    // Set initial view matrix
    Camera::updateView();

    // Set initial projection matrix
    Camera::updateProjection(1000, 1000);
}

/*
 * Overloaded Constructor.
 *
 * Parameters:
 *      screenWidth:        Width of screen
 *      screenHeight:       Height of screen
 *      cameraPosition:     Initial position of the camera as a vec3
 *      cameraUp:           Initial up direction of the world as a vec3
 *      yaw:                Initial yaw of the camera as a vec3
 *      pitch:              Initial pitch of the camera as a vec3
 */
Camera::Camera(GLfloat screenWidth, GLfloat screenHeight, glm::vec3 cameraPosition, glm::vec3 cameraUp, GLfloat yaw, GLfloat pitch) {
    // Set initial camera position and world orientation
    this->cameraPosition = cameraPosition;
    this->cameraFront = glm::vec3(0.0f, -1.0f, -20.0f);
    this->lastCameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
    this->cameraUp = cameraUp;

    // Set initial tilt of camera
    this->roll = 0.0f;
    this->yaw = yaw;
    this->pitch = pitch;

    // Set front, right and up vectors
    Camera::updateView();

    // Set initial model location
    this->rotateFactor = 0.0f;
    this->translationStart = glm::vec3(0.000f, 0.000f, 0.000f);
    this->rotationStart = glm::vec3(1.000f, 0.000f, 0.000f);
    this->scaleStart = glm::vec3(0.075f, 0.075f, 0.075f);

    // Set initial model matrix
    this->model = glm::mat4(1.0f);
    Camera::updateModel(this->translationStart, this->rotationStart, this->scaleStart, rotateFactor);

    // Set initial view matrix
    Camera::updateView();

    // Set initial projection matrix
    Camera::updateProjection(screenWidth, screenHeight);
}

/*
 * Deconstructor.
 */
Camera::~Camera() {}


/*
 * Updates the model matrix.
 */
void Camera::updateModel(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale, GLfloat rotateFactor) {
    this->rotateFactor = rotateFactor;

    this->model = glm::mat4(1.0f);
    this->model = glm::translate(this->model, translation);
    this->model = glm::rotate(this->model, glm::radians(this->rotateFactor), rotation);
    this->model = glm::scale(this->model, scale);
}

/*
 * Updated camera vectors (front, right and up vectors).
 *
 * TODO: Adjust for z-axis.
 */
void Camera::updateView() {
    // Update the cameraFront vector
    glm::vec3 tempFront;
    tempFront.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    tempFront.y = sin(glm::radians(this->pitch));
    tempFront.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->cameraFront = glm::normalize(tempFront);

    // Update the cameraRight vector
    this->cameraRight = glm::normalize(glm::cross(this->cameraFront, this->cameraUp));

    // Update the cameraUp vector
    this->cameraUp = glm::normalize(glm::cross(this->cameraRight, this->cameraFront));

    this->view = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);
}

/*
 * Updates the projection matrix.
 */
void Camera::updateProjection(int width, int height) {
    //this->projection = glm::perspective(glm::radians(90.0f), float(width)/ float(height), 0.1f, 100.0f);
    this->projection = glm::perspective(glm::radians(this->fov), float(width) / float(height), 0.1f, 100.0f);
}

/*
 * Updates and returns the model matrix.
 *
 * Returns:
 *      mat4: model matrix
 */
glm::mat4 Camera::getModel() {
    return this->model;
}

/*
 * Updates and returns the view matrix.
 *
 * Returns:
 *      mat4: view matrix
 */
glm::mat4 Camera::getView() {
    return this->view;
}

/*
 * Updates and returns the projection matrix.
 *
 * Returns:
 *      mat4: projection matrix
 */
glm::mat4 Camera::getProjection() {
    return this->projection;
}

/*
 * Adjusts the position of the camera.
 *
 * Parameters:
 *      vec3: New position of the camera.
 */
void Camera::updateCameraPosition(glm::vec3 newPosition) {
    Camera::cameraPosition = newPosition;
}

/*
 * Adjusts the direction in which the camera faces.
 *
 * TODO: Adjust for z-axis.
 *
 * Parameters:
 *      vec3: New direction the camera faces.
 */
void Camera::updateCameraDirection(glm::vec3 newDirection) {
    // Calculate change from last frame, if any
    float xOffset = newDirection[0] - this->lastCameraDirection[0];
    float yOffset = this->lastCameraDirection[1] - newDirection[1];
    this->lastCameraDirection = newDirection;

    // Update pitch and yaw
    this->pitch += xOffset;
    this->yaw += yOffset;

    // Clamp pitch
    (this->pitch > 89.0f) ? this->pitch = 89.0f : this->pitch;
    (this->pitch < -89.0f) ? this->pitch = -89.0f : this->pitch;

    Camera::updateView();
}

/*
 * Adjusts the fov of the camera.
 *
 * Parameters:
 *      GLfloat: New fov factor.
 */
void Camera::updateCameraZoom(GLfloat newFOV) {
    // Update fov
    this->fov = newFOV;

    // Clamp fov in range [1, 90]
    (this->fov > 180.0f) ? this->fov = 180.0f : this->fov;
    (this->fov < 1.0f) ? this->fov = 1.0f : this->fov;
}























