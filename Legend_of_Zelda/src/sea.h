#include "main.h"

#ifndef SEA_H
#define SEA_H


class Sea
{
	public:
	    Sea() {}
	    Sea(float y);
	    void draw(glm::mat4 VP);
	    glm::vec3 position;
	
	private:
	    VAO *object;
};

#endif // SEA_H
