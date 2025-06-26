#pragma once

#include <vector>
#include <functional>
#include <memory>

#include "Vertex.h"

#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"

class Grapher
{
public:
    Transform transform;

    Grapher();
    ~Grapher();

    void drawAxis(const Shader& shader, const Mesh& mesh, const glm::vec3 color);
    void drawAxes(const Shader& shader);
    void drawFunction(const Shader& shader);
    void loadFunction(std::function<float(float, float)> func);

private:
    std::vector<Vertex> x_axis = {
        {{1.0f, 0.0f, 0.0f}, glm::vec3(0.0f), glm::vec2(0.0f)},
        {{-1.0f, 0.0f, 0.0f}, glm::vec3(0.0f), glm::vec2(0.0f)},
    };

    std::vector<Vertex> y_axis = {
        {{0.0f, 1.0f, 0.0f}, glm::vec3(0.0f), glm::vec2(0.0f)},
        {{0.0f, -1.0f, 0.0f}, glm::vec3(0.0f), glm::vec2(0.0f)},
    };

    std::vector<Vertex> z_axis = {
        {{0.0f, 0.0f, 1.0f}, glm::vec3(0.0f), glm::vec2(0.0f)},
        {{0.0f, 0.0f, -1.0f}, glm::vec3(0.0f), glm::vec2(0.0f)},
    };

    Mesh AxisMeshX;
    Mesh AxisMeshY;
    Mesh AxisMeshZ;

    std::unique_ptr<Mesh> FunctionSurfaceMesh;

    //* Precision
    float dx = 1.0f;
    float dy = 1.0f;

    float xMin = -10;
    float xMax = 10;

    float yMin = -10;
    float yMax = 10;
};