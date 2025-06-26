#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "Shader.h"

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    void load(const std::string& name, const std::string& verPath, const std::string& fragPath);
    Shader& get(const std::string& name);

private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;

};