//
// Created by breki on 8/11/2023.
//

#ifndef TRIANGLE_WINDOW_H
#define TRIANGLE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window {
public:
    GLFWwindow* init();

    int height;

    int width;

private:
    static void framebuffer_size_callback3(GLFWwindow* window, int width, int height);
};


#endif //TRIANGLE_WINDOW_H
