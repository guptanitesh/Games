#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color, int flag);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);


private:
    VAO *object;
};

#endif