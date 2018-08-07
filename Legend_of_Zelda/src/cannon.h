#include "main.h"

#ifndef CANNON_H
#define CANNON_H

class Cannon
{
    public:
        Cannon() {}
        Cannon(float x, float y, float z);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        float rotation, vel, theta;
        int isAlive;
    
    private:
        VAO *object;
};

#endif // CANNON_H
