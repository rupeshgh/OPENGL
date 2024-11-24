#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <fstream>
#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Timestep.h"
#include "camera.h"

float deltatime;
using namespace std;

int main() {
    const unsigned int w_Width = 800;
    const unsigned int w_Height = 800;
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    window = glfwCreateWindow(w_Width, w_Height, "YoLo", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) // glewinit only after valid window context
        std::cout << "glew not ok" << std::endl;

    GLfloat vertices[] = {
        // cordinates		//colors			//tex cordinate
        -0.5f, 0.0f, 0.5f, 0.0f, 0.70f, 0.44f, 0.0f, 0.0f, -0.5f, 0.0f,
        -0.5f, 0.0f, 0.80f, 0.0f, 5.0f, 0.0f, 0.5f, 0.0f, -0.5f, 0.83f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.83f, 0.0f, 0.0f,
        5.0f, 0.0f, 0.0f, 0.8f, 0.0f, 0.92f, 0.0f, 0.76f, 2.5f, 5.0f
    };

    // Indices for vertices order
    GLuint indexes[] = {
        0, 1, 2, 0, 2, 3, 0, 1, 4, 1,
        2, 4, 2, 3, 4, 3, 0, 4

    };

    GLfloat cubeVertices[] = {
        // Position coordinates       // Color (Yellow)
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // Back bottom-left
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // Back bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // Back top-right
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // Back top-left

        -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, // Front bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, // Front bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, // Front top-right
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, // Front top-left
    };

    GLuint cubeIndices[] = {
        // Back face
        0, 1, 2, 2, 3, 0,

        // Front face
        4, 5, 6, 6, 7, 4,

        // Left face
        0, 4, 7, 7, 3, 0,

        // Right face
        1, 5, 6, 6, 2, 1,

        // Bottom face
        0, 1, 5, 5, 4, 0,

        // Top face
        3, 2, 6, 6, 7, 3
    };

    // using compile time absolute path ...as runtime concatenated with cmake
    // build dir
    std::string file_path = __FILE__;
    size_t pos = file_path.find_last_of("/\\"); // Handle both Linux and Windows
    string srcPath1 = (pos == std::string::npos) ? "" : file_path.substr(0, pos);
    string srcPath2 = (pos == std::string::npos) ? "" : file_path.substr(0, pos);

    string vertexShaderPath = srcPath1.append("/default.vert");
    string fragmentShaderPath = srcPath2.append("/default.frag");

    shader shaderProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    // use this if you have vertex and fragment shader on different file

    // can use single shader file as well should include vertex and frag..
    // currently issue with this shader shaderProgram("path to single shader
    // file");
    // use this if you have vertex and fragment shader on same file
    // shader shaderProgram("Basic.shader");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indexes, sizeof(indexes));

    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *) 0);
    VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *) (sizeof(float) * 3));
    VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *) (sizeof(float) * 6));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    //
    VAO vao2;
    vao2.Bind();

    VBO vbo2(cubeVertices, sizeof(cubeVertices));
    EBO ebo2(cubeIndices, sizeof(cubeIndices));

    vao2.linkAttrib(vbo2, 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *) 0);
    vao2.linkAttrib(vbo2, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6,
                    (void *) (sizeof(float) * 3));

    vao2.Unbind();
    vbo2.Unbind();
    ebo2.Unbind();

    static float Scale = 1.0f;
    static float Delta = 0.0005f;

    // GLint ScaleLocation = glGetUniformLocation(shaderProgram.ID, "gScale");

    glEnable(GL_DEPTH_TEST);
    // glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    // camera
    camera cam(w_Width, w_Height, glm::vec3(0.0f, 0.3f, 1.0f));

    Timestep timestep;
    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    float lastFrame = 0.0;
    float deltaTime;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);

        // todo:may need to toogle if different shader program exist
        shaderProgram.Activate();

        double currTime = glfwGetTime();
        if (currTime - prevTime >= 1 / 60) {
            rotation += 0.3f;
            prevTime = currTime;
        }

        // camera connected to the clipped projected plane
        cam.matrix(90.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        cam.inputs(window, timestep);

        float currentFrame = (float) glfwGetTime();
        timestep = currentFrame - lastFrame;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Scale += Delta;
        if ((Scale >= 1.0f) || (Scale <= -1.0f)) {
            Delta *= -1.0f;
        }

        // glUniform1f(ScaleLocation, Scale);

        glm::mat4 unitMatrix = glm::mat4(1.0f); // Init with a unit matrix

        glm::mat4 rotatedPyramid =
                glm::rotate(unitMatrix, glm::radians(rotation),
                            glm::vec3(0.f, 1.f, 0.0f)); // rotation about y-axis
        //
        glm::mat4 pyramdiTranslated = glm::translate(
            glm::mat4(1.0f),
            glm::vec3(-0.3f, -0.5f, -1.0f)); // model to world cordinate by view *model*pos
        int viewLocation = glGetUniformLocation(shaderProgram.ID, "view"); //

        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(pyramdiTranslated ));
        // glUniformMatrix4fv(modelLocation, 1, GL_FALSE,

        // glUniform1f(ScaleLocation, Scale);
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indexes) / sizeof(unsigned int),
                       GL_UNSIGNED_INT, nullptr);
        VAO1.Unbind();

        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        vao2.Bind();
        glm::mat4 rotatedCube= glm::rotate(unitMatrix, glm::radians(3*rotation),glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 cubeScaled =glm::scale(unitMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
        glm::mat4 translatedCube = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, -0.2f));

        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr( rotatedCube*  translatedCube  *cubeScaled));
        //
        glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(unsigned int),
                       GL_UNSIGNED_INT, nullptr);
        vao2.Unbind();
        //
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    //
    vao2.Delete();
    vbo2.Delete();
    shaderProgram.Delete();

    glfwTerminate();

    return 0;
}
