#include "main.h"

#ifndef PLANK_H
#define PLANK_H


class Plank
{
public:
    Plank(){};
    Plank(float x, float y, float rotation, float velx, color_t color);
    glm::vec3 position;
    int flag;
    double velx;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object1;
    VAO *object2;
};

#endif 