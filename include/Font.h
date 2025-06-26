#pragma once

#include <string>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct Character{
    GLuint TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    GLuint Advance;
}Character;

class Font
{
public:
    Font(std::string path);
    Character getCharacter(char c);

private:
    std::map<char, Character> Characters;

};