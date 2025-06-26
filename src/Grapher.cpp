#include "Grapher.h"

Grapher::Grapher() : AxisMeshX(x_axis, GL_LINES),
                     AxisMeshY(y_axis, GL_LINES),
                     AxisMeshZ(z_axis, GL_LINES)
{
    AxisMeshX.transform.scale *= 10;
    AxisMeshY.transform.scale *= 10;
    AxisMeshZ.transform.scale *= 10;
}

Grapher::~Grapher() 
{
}

void Grapher::drawAxes(const Shader &shader)
{
    drawAxis(shader, AxisMeshX, {1.0f, 0.0f, 0.0f});
    drawAxis(shader, AxisMeshY, {0.0f, 1.0f, 0.0f});
    drawAxis(shader, AxisMeshZ, {0.0f, 0.0f, 1.0f});
}

void Grapher::drawAxis(const Shader &shader, const Mesh &mesh, const glm::vec3 color)
{
    glm::mat4 model = mesh.transform.getModelMatrix();
    shader.setVec3("objectColor", color);
    shader.setMat4("model", model);
    glLineWidth(3.0f); //* ???
    mesh.draw();
}

void Grapher::loadFunction(std::function<float(float, float)> func)
{
    

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int index = 0;

    for (float x = xMin; x < xMax; x += dx)
    {
        for (float y = yMin; y < yMax; y += dy)
        {
            float z = func(x, y);
            glm::vec3 p0 = {x, z, y};

            if (x + dx <= xMax)
            {
                float zRight = func(x + dx, y);
                glm::vec3 p1 = {x + dx, zRight, y};

                vertices.push_back({p0, {}, {}});
                vertices.push_back({p1, {}, {}});

                indices.push_back(index++);
                indices.push_back(index++);
            }

            if (y + dy <= yMax)
            {
                float zUp = func(x, y + dy);
                glm::vec3 p2 = {x, zUp, y + dy};

                vertices.push_back({p0, {}, {}});
                vertices.push_back({p2, {}, {}});

                indices.push_back(index++);
                indices.push_back(index++);
            }
        }
    }

    // Créer un mesh avec vertices et indices une fois
    FunctionSurfaceMesh = std::make_unique<Mesh>(vertices, indices, GL_LINES);

}

void Grapher::drawFunction(const Shader &shader)
{
    glm::mat4 model = FunctionSurfaceMesh->transform.getModelMatrix();
    shader.setVec3("objectColor", {1.0f, 1.0f, 1.0f});
//    shader.setVec3("objectColor", {0.7f, 0.1f, 0.6f});
    shader.setMat4("model", model);
    glLineWidth(3.0f); //* ???
    FunctionSurfaceMesh->draw();
}