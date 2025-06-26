#pragma once

#include <string>
#include <memory>

#include <glm/glm.hpp>

#include "Transform.h"
#include "Shader.h"

class Light
{
public:
    Transform transform;
    glm::vec3 color;

    virtual void apply(Shader& shader, const std::string& name) const = 0;
    virtual ~Light() = default;
};