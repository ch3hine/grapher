#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Texture
{
public:
    unsigned int ID;
    unsigned int slot;

    Texture(unsigned int slot = 0);
    ~Texture();

    void loadFromFile(const char* path);
    void use()const;

};