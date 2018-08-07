#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat
{
    public:
    
        Boat() {}
        Boat(float x, float y, float z);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        float vel, vely, ltheta, omega, ay, vel_y, rotation, g;
            
    private:
        VAO *object9;
        VAO *object8;
        VAO *object7;
        VAO *object6;
        VAO *object5;
        VAO *object4;
        VAO *object3;
        VAO *object2;
        VAO *object1;
};

#endif // Boat_H
