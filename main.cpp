//
// Created by Breki on 19/07/2023.
//
#ifndef MAIN_H
#define MAIN_H
#include "triangle.h"
//#include "ShaderExample.h"
//#include "textureExample.h"
#include "transformationExample.h"

int main() {
    // return Triangle().runTriangle();
    // return ShaderExample().runShaders();
    // return textureExample().run();
    return transformationExample().run();
}
#endif