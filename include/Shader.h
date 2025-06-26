#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    

private:
    std::string readFile(const std::string& path);
    GLuint compileShader(const char* source, GLenum shaderType);
};