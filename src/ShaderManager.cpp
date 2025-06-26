#include "ShaderManager.h"

ShaderManager::ShaderManager()
{

}


void ShaderManager::load(const std::string& name, const std::string& verPath, const std::string& fragPath)
{
    shaders[name] = std::make_unique<Shader>(verPath.c_str(), fragPath.c_str());
}

Shader& ShaderManager::get(const std::string& name)
{
    auto it = shaders.find(name);
    if (it != shaders.end())
        return *(it->second);
    else
        throw std::runtime_error("Shader not found: " + name);
}

ShaderManager::~ShaderManager()
{
}

