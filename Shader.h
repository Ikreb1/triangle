//
// Created by Breki on 21/07/2023.
//
#pragma once
#ifndef TRIANGLE_SHADER_H
#define TRIANGLE_SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"


class Shader {
public:
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader();
    // the program ID
    unsigned int ID;

    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;

private:
    static void checkCompileErrors(unsigned int shader, const std::string& type);
};


#endif //TRIANGLE_SHADER_H
