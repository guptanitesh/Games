#include "main.h"

#ifndef BOOSTER_H
#define BOOSTER_H


class Booster
{
    public:
        Booster() {}
        Booster(float x, float y, float z);
        void draw(glm::mat4 VP);
        glm::vec3 position;
        float rotation;
        int isAlive;
        
    private:
        VAO *object;
};

#endif // BOOSTER_H
