//
// Created by Breki on 21/07/2023.
//
#pragma once
#ifndef TRIANGLE_TEXTURE_H
#define TRIANGLE_TEXTURE_H


class texture {
public:
    unsigned int ID;

    explicit texture(const char* texturePath, bool alpha = false);
};


#endif //TRIANGLE_TEXTURE_H
