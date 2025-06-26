#pragma once

#include <vector>
#include "Vertex.h"

enum class PrimitiveType {
    Cube,
    Quad,
    Sphere,
    Plane
};

namespace Primitives{

    extern const std::vector<Vertex> CubeVertices;
    extern const std::vector<unsigned int> CubeIndices;

    extern const std::vector<Vertex> QuadVertices;
extern const std::vector<unsigned int> QuadIndices;


}