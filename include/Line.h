#pragma once

#include <vector>

#include "Vertex.h"
#include "Mesh.h"
#include "Shader.h"

class Line
{
public:
    Line();

    void draw(const Shader& shader);

private:
    std::vector<Vertex> line_data = {
        {{1.0f, 0.0f, 0.0f}, glm::vec3(0.0f), glm::vec2(0.0f)},
        {{-1.0f, 0.0f, 0.0f}, glm::vec3(0.0f), glm::vec2(0.0f)}
    };

    Mesh LineMesh;
    glm::vec3 Color;
};