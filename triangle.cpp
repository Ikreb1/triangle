//
// Created by Breki on 19/07/2023.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "triangle.h"

void framebuffer_size_callback2(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

const float speed = 0.01f;
bool red = false;
int backgroundInputDelay = 0;
bool isTriangle = true;

float triangle[] = {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
        1.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
        0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Vertex 3: Blue
        // Triangle 2
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
        -1.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
        0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
};

float square[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
};

unsigned int squareIndices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

void process_input(GLFWwindow* window)
{
    if (backgroundInputDelay > 0)
    {
        backgroundInputDelay--;
    }
    // close window on escape key press
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (red)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        triangle[0] += speed;
        triangle[6] += speed;
        triangle[12] += speed;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        triangle[0] -= speed;
        triangle[6] -= speed;
        triangle[12] -= speed;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        triangle[1] += speed;
        triangle[7] += speed;
        triangle[13] += speed;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        triangle[1] -= speed;
        triangle[7] -= speed;
        triangle[13] -= speed;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && backgroundInputDelay == 0)
    {
        red = !red;
        if (red)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        backgroundInputDelay = 10;
    }
}

const GLchar* vertexSource = R"glsl(
    #version 330 core
    in vec3 position;
    in vec3 color;
    out vec3 Color;
    void main()
    {
        Color = color;
        gl_Position = vec4(position, 1.0);
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 330 core
    in vec3 Color;
    out vec4 outColor;
    void main()
    {
        outColor = vec4(Color, 1.0);
    }
)glsl";

int Triangle::runTriangle() {
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
        return -1;
    }
    glfwMakeContextCurrent(window);
    // resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback2);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // set viewport size
    glViewport(0, 0, 800, 600);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    unsigned int VBOs[2], VAOs[2], EBO;
    glGenVertexArrays(2, &VAOs[0]);
    if (isTriangle)
    {
        glGenBuffers(2, VBOs);
    }
    else
    {
        glGenBuffers(2, VBOs);
        glGenBuffers(1, &EBO);
    }
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOs[0]);

    if (isTriangle)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

        glBindVertexArray(VAOs[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
    }

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    for (int i=0;i<2;i++)
    {
        glBindVertexArray(VAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        // link shaders
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);
        // Specify the layout of the vertex data
        int posAttrib = glGetAttribLocation(shaderProgram, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 3, GL_FLOAT, false, 6 * sizeof(float), nullptr);

        int colAttrib = glGetAttribLocation(shaderProgram, "color");
        glEnableVertexAttribArray(colAttrib);
        glVertexAttribPointer(colAttrib, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }

    // render loop
    while(!glfwWindowShouldClose(window))
    {
        process_input(window);

        // render commands
        // state-setting function
        if (red)
        {
            glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
        }
        else
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        if (isTriangle)
        {
            // TODO: Only do when needed to move triangle
            glBindVertexArray(VAOs[0]);
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(VAOs[1]);
            glDrawArrays(GL_TRIANGLES, 3, 3);
        } else
        {
            glBindVertexArray(VAOs[0]);
            glBindVertexArray(VAOs[1]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glfwTerminate();
    return 0;
}
