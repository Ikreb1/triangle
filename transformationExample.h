//
// Created by breki on 8/3/2023.
//
#pragma once
#ifndef TRIANGLE_TRANSFORMATIONEXAMPLE_H
#define TRIANGLE_TRANSFORMATIONEXAMPLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

class transformationExample {
public:
    int run(GLFWwindow* window);

private:
    void process_input(GLFWwindow* window);

    bool toggleWireframe = false;
    int backgroundInputDelay = 0;

    float vertices[32] = {
            -0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // top right
            -0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // bottom right
            0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // bottom left
            0.5f,  -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f    // top left
    };

    unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    float mixValue = 1.0f;
};


#endif //TRIANGLE_TRANSFORMATIONEXAMPLE_H
