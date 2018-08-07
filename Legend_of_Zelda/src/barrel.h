#include "main.h"

#ifndef BARREL_H
#define BARREL_H


class Barrel
{
	public:
	    Barrel() {}
	    Barrel(float y);
	    glm::vec3 position;
	    float rotation;
	    void draw(glm::mat4 VP);
	
	private:
	    VAO *object;
	    VAO *object1;
};

#endif // BARREL_H
