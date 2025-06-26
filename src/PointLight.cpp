#include "PointLight.h"

void PointLight::apply(Shader& shader, const std::string& name) const
{
    shader.setVec3(name + ".position", position);
    shader.setVec3(name + ".color", color);
}