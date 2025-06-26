#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
    glm::vec3 direction;
    void apply(Shader& shader, const std::string& name) const override;
};