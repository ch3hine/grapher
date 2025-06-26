#pragma once

#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    Transform transform;

    Camera();
    ~Camera();

    glm::mat4 getViewMatrix()const;

    glm::mat4 getProjectionMatrix(float aspectRatio, float nearPlane = 0.1f, float farPlane = 100.0f)const;

    void setFov(float fov);
    float getFov()const;

    void processKeyboard(CameraMovement direction, float deltaTime);

private:
    float yaw = -90.0f;  // initialisé vers l'axe -Z
    float pitch = 0.0f;  // optionnel, pour rotation verticale
    float rotationSpeed = 45.0f; // degrés par seconde
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float fov; 
    float speed = 3.0f; // unités par seconde
};