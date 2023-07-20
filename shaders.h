//
// Created by Breki on 20/07/2023.
//
#pragma once
#ifndef TRIANGLE_SHADERS_H
#define TRIANGLE_SHADERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class shaders {
public:
    int runShaders();

private:
    void process_input(GLFWwindow* window);
    GLFWwindow* init();

    const char* vertexSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

    out vec4 vertexColor; // specify a color output to the fragment shader

    void main()
    {
        gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
        vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
    }
    )glsl";

    const char* fragmentSource = R"glsl(
    #version 330 core
    out vec4 FragColor;

    in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)

    void main()
    {
        FragColor = vertexColor;
    }
    )glsl";

    bool toggleWireframe = false;
    int backgroundInputDelay = 0;

    float triangle[18] = {
            0.5f,  0.5f, 0.0f,
            1.0f, -0.5f, 0.0f,
            0.0f, -0.5f, 0.0f,
            /*
            // Triangle 2
            -0.5f,  0.5f, 0.0f,
            -1.0f, -0.5f, 0.0f,
            0.0f, -0.5f, 0.0f
             */
    };
};


#endif //TRIANGLE_SHADERS_H
