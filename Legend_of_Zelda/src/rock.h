#include "main.h"

#ifndef ROCK_H
#define ROCK_H


class Rock
{
    public:
        Rock() {}
        Rock(float y);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        float rotation;
    private:
        VAO *object;
};

#endif // ROCK_H
