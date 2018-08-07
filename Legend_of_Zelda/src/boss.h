#include "main.h"

#ifndef BOSS_H
#define BOSS_H

class Boss
{
    public:
        Boss() {}
        Boss(float x, float y, float z);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        int isAlive, life;
        float rotation, vel;

    private:
        VAO *object;
};

#endif // BOSS_H
