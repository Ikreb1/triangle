//
// Created by Breki on 19/07/2023.
//
#ifndef MAIN_H
#define MAIN_H
#include "triangle.h"
//#include "ShaderExample.h"
//#include "textureExample.h"
#include "transformationExample.h"
#include "Window.h"
#include "CoordSystemExample.h"

int main() {
    auto window = new Window();
    auto windowPtr = window->init();
    // return Triangle().runTriangle();
    // return ShaderExample().runShaders();
    // return textureExample().run();
    // return transformationExample().run(windowPtr);
    return CoordSystemExample().run(windowPtr);
}
#endif