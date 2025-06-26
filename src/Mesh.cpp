#include "Mesh.h"

Mesh::Mesh(){}

Mesh::Mesh(PrimitiveType type, GLenum primitiveType)
{
    switch (type)
    {
    case PrimitiveType::Cube:
        vertices = Primitives::CubeVertices;
        indices = Primitives::CubeIndices;
        this->primitiveType = primitiveType;
        break;
    case PrimitiveType::Quad:
        vertices = Primitives::QuadVertices;
        indices = Primitives::QuadIndices;
        this->primitiveType = primitiveType;
        break;
    }


    setupMesh();
}


Mesh::Mesh(const std::vector<Vertex>& vertices, GLenum primitiveType) : 
    vertices(vertices),
    primitiveType(primitiveType) 
{

    setupMesh();
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, GLenum primitiveType):
    vertices(vertices),
    indices(indices),
    primitiveType(primitiveType)
{
    setupMesh();
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &VBO);
    if(indicesCount != 0)
        glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);

}

void Mesh::draw()const
{
    glBindVertexArray(VAO);
    if(indicesCount == 0)
    {
        glDrawArrays(primitiveType, 0, vertexCount);
    }else
        glDrawElements(primitiveType, indicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh()
{
    vertexCount = vertices.size();
    indicesCount = indices.size();

    //* Gen VAO, VBO and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    if(indicesCount != 0)
        glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); //? enable object to configure it

    //* VBO : Vertices data
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //? enable object to configure it
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW); //? copy array buffon from CPU to GPU mem

    if(indicesCount != 0)
    {
        //* EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }

    //* Configure vertex attributes

    //* Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    //* Normal Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    
    
    //* TexCoords Attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    //* Unbind VBO and VAO (security)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}