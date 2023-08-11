//
// Created by breki on 8/11/2023.
//

#ifndef TRIANGLE_COORDSYSTEMEXAMPLE_H
#define TRIANGLE_COORDSYSTEMEXAMPLE_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

class CoordSystemExample {
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


#endif //TRIANGLE_COORDSYSTEMEXAMPLE_H
