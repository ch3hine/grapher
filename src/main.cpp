#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <map> 

#include "Shader.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Grapher.h"
#include "ShaderManager.h"
#include "Font.h"
#include "Text.h"

#define BACKGROUND_COLOR {0,0,0}


//* VBO : Stores vertices 
//* VAO : Reading configuration
//* glVertexAttribPointer: TODO
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "Size changed" << std::endl;
    glViewport(0, 0, width, height);
}

std::map<char, Character> Characters;

GLuint VAO, VBO;

void initTextRendering() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW); //* Or static

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void renderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color, Font& font) {
    shader.use();
    shader.setInt("text", 0);
    shader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (char c : text) {
        //Character ch = Characters[c];
        Character ch = font.getCharacter(c);

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        //* Vertex Version
        // std::vector<Vertex> verticesVec = {
        //     { glm::vec3(xpos,     ypos + h, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f) },
        //     { glm::vec3(xpos,     ypos,     0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
        //     { glm::vec3(xpos + w, ypos,     0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) },

        //     { glm::vec3(xpos,     ypos + h, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f) },
        //     { glm::vec3(xpos + w, ypos,     0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) },
        //     { glm::vec3(xpos + w, ypos + h, 0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) }
        // };


        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) std::cout << "GL error: " << err << std::endl;

        x += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

int main(int argc, char** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "My Window", NULL, NULL);
    if (!window)
    {
        std::cerr << "Error while creating window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initial viewport
    glViewport(0, 0, 800, 600);

    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    glEnable(GL_DEPTH_TEST);

    {

        ShaderManager shaderManager;

        shaderManager.load("basic","/home/chach/projects/grapher/src/shaders/vert.glsl","/home/chach/projects/grapher/src/shaders/frag.glsl");
        shaderManager.load("text","/home/chach/projects/grapher/src/shaders/text_vert.glsl","/home/chach/projects/grapher/src/shaders/text_frag.glsl");

        Shader& shader = shaderManager.get("basic");
        Shader& textShader = shaderManager.get("text");

        //loadFont("/home/chach/projects/grapher/fonts/default.ttf");
        initTextRendering();

        Font font("/home/chach/projects/grapher/fonts/default.ttf");

        PointLight pl;
        pl.position = glm::vec3(0.0f, 0.0f, 0.0f);
        pl.color = glm::vec3(1.0f, 1.0f, 1.0f);

        DirectionalLight dl;
        dl.direction = glm::vec3(0.0f, 0.0f, 0.0f);
        dl.color = glm::vec3(1.0f, 1.0f, 1.0f);

        Texture tex(0);
        tex.loadFromFile("/home/chach/projects/grapher/crate.jpg");
        
        Mesh cubeMesh(PrimitiveType::Cube);

        auto func = [](float x, float y) { return x*x; };

        Text text;
        text.setLabel("OpenGL!");
        text.setFont(font);

        Grapher grapher;
        grapher.loadFunction(func);

        //* Camera

        Camera camera;
        camera.transform.position = glm::vec3(0.0f, 0.0f, 3.0f);
        camera.setFov(90.0f);

        //* Time

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        glfwSetWindowCloseCallback(window, [](GLFWwindow* win) {
            glfwSetWindowShouldClose(win, true);
        });

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            float rotationSpeed = 90.0f; // degrés par seconde

            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
                camera.transform.rotation.y -= rotationSpeed * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
                camera.transform.rotation.y += rotationSpeed * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.processKeyboard(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.processKeyboard(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.processKeyboard(LEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.processKeyboard(RIGHT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                camera.processKeyboard(UP, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                camera.processKeyboard(DOWN, deltaTime);


            glClearColor(0, 0, 0, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            float aspectRatio = 800.f/600.f;
            glm::mat4 view = camera.getViewMatrix();
            glm::mat4 projection = camera.getProjectionMatrix(aspectRatio);

            shader.use();
 
            //* Shaders params

            pl.apply(shader, "light");
            dl.apply(shader, "dirLight");

            shader.setVec3("viewPos", camera.transform.position);
            shader.setVec3("objectColor", {1.0f, 0.0f, 0.0f}); 

            shader.setMat4("view", view);
            shader.setMat4("projection", projection);

            //* DRAWING ZONE (z-index based)

            grapher.drawAxes(shader);
            grapher.drawFunction(shader);

            glm::mat4 projection2 = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
            textShader.use();
            textShader.setMat4("projection", projection2);

            glDisable(GL_DEPTH_TEST);
            text.draw(textShader);            
            glEnable(GL_DEPTH_TEST);



            // tex.use();
            // shader.setInt("useTexture", false);
            // shader.setInt("uTexture", 0);

            // {
            //     glm::mat4 model = cubeMesh.transform.getModelMatrix();
            //     model = glm::rotate(model, glm::radians(currentFrame * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            //     shader.setMat4("model", model);
            //     cubeMesh.draw();
            // }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
