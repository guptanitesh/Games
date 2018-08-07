#include "main.h"

#ifndef PORCUPINE_H
#define PORCUPINE_H


class Porcupine {
public:
    Porcupine() {}
    Porcupine(float x, float velx, color_t color); 
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double velx;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
