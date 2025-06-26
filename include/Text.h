#pragma once

#include <string>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Font.h"
#include "Shader.h"


class Text
{
public:
    Text();


    void setLabel(std::string label);
    void setFont(Font& font);

    void draw(const Shader& shader);

private:
    Font* font;
    std::string label;
    int posX, posY, scale;
    glm::vec3 color;

    //* Rendering
    GLuint VAO, VBO;


};