/**
 * Camera.cpp
 * Authors: Sheldon Taylor, Jiju Poovvancheri
 *
 * Implementation of a first person camera.
 */

#include "Camera.h"

int flagV = 0;
int flagP = 0;

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

    int typeFlag = 1;
    if (typeFlag == 0) {
        /// Imported Mesh
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
    } else if (typeFlag == 1) {
        /// Procedural Landscape
        // Set initial tilt of camera
        this->roll = 0.0f;
        this->yaw = yaw;
        this->pitch = pitch;

        this->cameraPosition = cameraPosition;

        glm::vec3 tempFront;///
        tempFront.x = sin(glm::radians(this->pitch));///
        tempFront.y = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));///
        tempFront.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));///

        this->cameraFront = glm::normalize(tempFront);///
        //this->cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
        this->cameraUp = cameraUp;

        glm::vec3 cameraDirection = glm::normalize(this->cameraFront - this->cameraPosition);///
        this->lastCameraDirection = cameraDirection;///
        this->cameraRight = glm::normalize(glm::cross(this->cameraUp, cameraDirection));
    } else {
        // TODO: throw error
    }

    // Set initial model matrix
    this->model = glm::mat4(1.0f);
    Camera::updateModel(this->translationStart, this->rotationStart, this->scaleStart, rotateFactor);

    // Update matrices
    Camera::updateView();
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


    int typeFlag = 1;
    if (typeFlag == 0) {
        /// Imported Mesh
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
    } else if (typeFlag == 1) {
        /// Procedural Landscape
        glm::vec3 tempFront;
        tempFront.x = sin(glm::radians(this->pitch));
        tempFront.y = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        tempFront.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

        this->cameraFront = glm::normalize(tempFront);                       // Z
        this->cameraRight = glm::normalize(glm::cross(this->cameraFront, this->cameraUp));          // Y
        this->cameraUp = glm::normalize(glm::cross(this->cameraRight, this->cameraFront));          // X

        //this->view = glm::lookAt(this->cameraPosition, this->cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
        this->view = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFront, this->cameraUp);
    } else {
        // TODO: throw error
    }

    // FIXME - DEBUG
    if (flagV++ < 0) {
        printf("    view matrix [%d]:\n    %f  %f  %f  %f\n    %f  %f  %f  %f\n    %f  %f  %f  %f\n    %f  %f  %f  %f\n", flagV,
               this->view[0][0], this->view[0][1], this->view[0][2], this->view[0][3],
               this->view[1][0], this->view[1][1], this->view[1][2], this->view[1][3],
               this->view[2][0], this->view[2][1], this->view[2][2], this->view[2][3],
               this->view[3][0], this->view[3][1], this->view[3][2], this->view[3][3]);
    }
}

/*
 * Updates the projection matrix.
 */
void Camera::updateProjection(int width, int height) {
    this->projection = glm::perspective(glm::radians(this->fov), float(width) / float(height), 0.1f, 1000.0f);

    // FIXME - DEBUG
    if (flagP++ < 0) {
        printf("    projection matrix [%d]:\n    %f  %f  %f  %f\n    %f  %f  %f  %f\n    %f  %f  %f  %f\n    %f  %f  %f  %f\n", flagP,
               this->projection[0][0], this->projection[0][1], this->projection[0][2], this->projection[0][3],
               this->projection[1][0], this->projection[1][1], this->projection[1][2], this->projection[1][3],
               this->projection[2][0], this->projection[2][1], this->projection[2][2], this->projection[2][3],
               this->projection[3][0], this->projection[3][1], this->projection[3][2], this->projection[3][3]);
    }
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
    this->cameraPosition = newPosition;
    //Camera::updateView();
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























