#include "Line.h"

Line::Line() :
    LineMesh(line_data, GL_LINES),
    Color({1.0f, 1.0f, 1.0f})
{
}

void Line::draw(const Shader& shader)
{
    glm::mat4 model = LineMesh.transform.getModelMatrix();
    shader.setVec3("objectColor", Color);
    shader.setMat4("model", model);
    glLineWidth(3.0f); //* ???
    LineMesh.draw();
}