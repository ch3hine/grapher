#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Vertex.h"
#include "Transform.h"
#include "Primitive.h"

class Mesh
{
public:
    Transform transform;

    Mesh();
    Mesh(PrimitiveType type, GLenum primitiveType = GL_TRIANGLES);

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, GLenum primitiveType = GL_TRIANGLES);
    Mesh(const std::vector<Vertex>& vertices, GLenum primitiveType = GL_TRIANGLES);

    ~Mesh();

    void draw()const;
private:
    void setupMesh();

    GLuint VAO, VBO, EBO;
    GLenum primitiveType;
    GLsizei vertexCount;
    size_t indicesCount;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

};