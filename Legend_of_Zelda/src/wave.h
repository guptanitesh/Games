#include "main.h"

#ifndef WAVE_H
#define WAVE_H


class Wave
{
    public:
        Wave() {}
        Wave(float y);
        float rotation;
        glm::vec3 position;
        void draw(glm::mat4 VP);
    private:
        VAO *object;
};

#endif // WAVE_H
