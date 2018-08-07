#include "porcupine.h"
#include "main.h"
#include <math.h>

Porcupine::Porcupine(float x, float velx, color_t color) 
{
    this->velx=velx;
    this->rotation = 0;
    this->position = glm::vec3(x, 0, 0);
    GLfloat vertex_buffer_data[] = {
        0, -1, 0,
        0.25, -1, 0,
        0.125, -0.65, 0,

        0.25, -1, 0,
        0.5, -1, 0,
        0.375, -0.65, 0,    

        0.5, -1, 0,
        0.75, -1, 0,
        0.625, -0.65, 0,

        0.75, -1, 0,
        1, -1, 0,
        0.875, -0.65, 0    
    };
  
    this->object = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, color, GL_FILL);
}

   
void Porcupine::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::tick()
{
    this->position.x += this->velx;
    if(this->position.x >= -3.25)
    {
        this->position.x = -3.25;
        this->velx = -(this->velx);
    }
    if(this->position.x <= -4)
    {
        this->position.x = -4;
        this->velx = -(this->velx);
    }
}
