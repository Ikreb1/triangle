//
// Created by Breki on 20/07/2023.
//

#include "ShaderExample.h"
#include "Shader.h"
#include <cmath>
#include <iostream>
#include <valarray>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ShaderExample::process_input(GLFWwindow* window)
{
    if (backgroundInputDelay > 0)
    {
        backgroundInputDelay--;
    }
    // close window on escape key press
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && backgroundInputDelay == 0)
    {
        if (toggleWireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        toggleWireframe = !toggleWireframe;
        backgroundInputDelay = 10;
    }
}

GLFWwindow* ShaderExample::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); if apple

    auto* window = glfwCreateWindow(800, 600, "TRIANGLE!!!", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    // resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    // set viewport size
    glViewport(0, 0, 800, 600);
    return window;
}

int ShaderExample::runShaders() {
    auto window = init();
    if (!window)
    {
        return -1;
    }
    const char* vertexSource = R"(C:\git\triangle\shaders\horiShader.vert)";
    const char* fragmentSource = R"(C:\git\triangle\shaders\horiShader.frag)";
    Shader ourShader = Shader(vertexSource, fragmentSource);
    ourShader.use();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleWithColor), triangleWithColor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // update the uniform color
    float offset = 0.0f;
    ourShader.setFloat("xOffset", offset);

    // render loop
    while(!glfwWindowShouldClose(window))
    {
        process_input(window);

        // render commands
        // state-setting function
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime();
        float funky = sin(time) / 1.f;
        ourShader.setFloat("funky", funky);

        // draw our first triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
