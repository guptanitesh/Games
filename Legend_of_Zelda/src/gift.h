#include "main.h"

#ifndef GIFT_H
#define GIFT_H

class Gift
{
    public:
        Gift() {}
        Gift(float x, float y, float z);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        int isAlive;
        float rotation;
    
    private:
        VAO *object;
};

#endif // GIFT_H
