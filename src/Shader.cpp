#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vCode = readFile(vertexPath);
    std::string fCode = readFile(fragmentPath);

    GLuint vshader = compileShader(vCode.c_str(), GL_VERTEX_SHADER);
    GLuint fshader = compileShader(fCode.c_str(), GL_FRAGMENT_SHADER);

    ID = glCreateProgram();
    glAttachShader(ID, vshader);
    glAttachShader(ID, fshader);
    glLinkProgram(ID);

    //* Verifications
    GLint success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "Error when linking program: " << infoLog << std::endl;
    }

    //* Free
    glDeleteShader(vshader);
    glDeleteShader(fshader);
    glDetachShader(ID, vshader);
    glDetachShader(ID, fshader);

}


void Shader::use() const 
{
    glUseProgram(ID);
}

void Shader::setInt(const std::string& name, int value)const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()),value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value)const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const 
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

std::string Shader::readFile(const std::string& path)
{
    std::ifstream file(path);
        if(!file)
        {
            std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
            return "";
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
}

GLuint Shader::compileShader(const char* source, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr );
    glCompileShader(shader);

    //* Verification of compilation
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        //* Retreive message in case of error
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error while compiling shader: " << infoLog << std::endl;
        return 0;
    }

    return shader;
}

Shader::~Shader()
{
    if (ID != 0){
        glDeleteProgram(ID);
        ID = 0;
    }
}