//
// Created by Breki on 20/07/2023.
//
#pragma once
#ifndef TRIANGLE_SHADEREXAMPLE_H
#define TRIANGLE_SHADEREXAMPLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderExample {
public:
    int runShaders();

private:
    void process_input(GLFWwindow* window);
    GLFWwindow* init();

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

    float triangleWithColor[24] = {
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };
};


#endif //TRIANGLE_SHADEREXAMPLE_H
