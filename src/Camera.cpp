#include "Camera.h"

Camera::Camera() : fov(45.0f)
{
    transform.rotation = glm::vec3(0.0f, -90.0f, 0.0f);
}


glm::mat4 Camera::getViewMatrix()const
{
    //* Position de la camera
    glm::vec3 position = transform.position;

    //* Direction frontale de la camera
    glm::vec3 front = transform.getFrontVector();

    //* Direction UP
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio, float nearPlane, float farPlane)const
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::setFov(float fov)
{
    this->fov = fov;
}

float Camera::getFov()const
{
    return fov;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = speed * deltaTime;
    glm::vec3 forward = glm::normalize(transform.getFrontVector());
    glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
    glm::vec3 up = glm::normalize(glm::cross(right, forward)); // worldUp, ou recalculez avec pitch/yaw

    switch (direction) {
        case FORWARD:  transform.position += forward * velocity; break;
        case BACKWARD: transform.position -= forward * velocity; break;
        case LEFT:     transform.position -= right * velocity; break;
        case RIGHT:    transform.position += right * velocity; break;
        case UP:       transform.position += up * velocity; break;
        case DOWN:     transform.position -= up * velocity; break;
    }
}

Camera::~Camera(){}
