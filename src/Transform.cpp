#include "Transform.h"

glm::mat4 Transform::getModelMatrix()const
{
    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::translate(mat, position);
    mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1,0,0));
    mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0,1,0));
    mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0,0,1));
    mat = glm::scale(mat, scale);
    return mat;
}

glm::vec3 Transform::getFrontVector() const
{
    //* Euler angles

    float pitch = rotation.x;
    float yaw = rotation.y;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    return glm::normalize(front);
}

