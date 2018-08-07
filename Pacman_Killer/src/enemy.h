#include "main.h"
#include "plank.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{
	public:
	    Enemy() {}
	    Enemy(float x, float y);
	    glm::vec3 position;
	    float rotation;
	    int flag, clr, pl;
	    Plank ply;
	    void draw(glm::mat4 VP);
	    bounding_box_t bounding_box();
		void tick();	
	    double r, velx;
	private:
	    VAO *object;
};

#endif