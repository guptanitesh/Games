#include "main.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H


class Trampoline {
public:
    Trampoline() {}
    Trampoline(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    int l;
    double beg, end, top;
    void draw(glm::mat4 VP);


private:
    VAO *object;
};

#endif