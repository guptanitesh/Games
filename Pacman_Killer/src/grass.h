#include "main.h"

#ifndef GRASS_H
#define GRASS_H


class Grass
{
	public:
	    Grass() {}
	    Grass(float x, float y, color_t color);
	    glm::vec3 position;
	    float rotation;
	    void draw(glm::mat4 VP);
	
	private:
	    VAO *object;
};

#endif