#pragma once

#include "Shader.h"
#include "Light.h"

class PointLight : public Light
{
public:
    glm::vec3 position;

    void apply(Shader& shader, const std::string& name) const override;
};