#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H

class Monster
{
    public:
        Monster() {}
        Monster(float y);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        float rotation, vel;
        int isAlive;

    private:
        VAO *object;
};

#endif // MONSTER_H
