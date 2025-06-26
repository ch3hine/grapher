#include "DirectionalLight.h"


void DirectionalLight::apply(Shader& shader, const std::string& name) const
{
    shader.setVec3(name + ".direction", direction);
    shader.setVec3(name + ".color", color);
}
