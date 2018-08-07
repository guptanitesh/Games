#include "plank.h"
#include "main.h"

Plank::Plank(float x, float y, float rotation, float velx, color_t color)
{
    this->rotation = rotation;
    this->velx = velx;
    this->position = glm::vec3(x, y, 0);
 
    const GLfloat rect_vertex_buffer_data[] = 
    {
        0, 0.07, 0,
        -0.6,  0.07, 0,
        0,  0, 0,
     
        0, 0, 0,
        -0.6,  0, 0,
        -0.6,  0.07, 0,

        0, 0.07, 0,
        0.3, 0.07, 0,
        0,  0, 0,

        0, 0, 0,
        0.3,  0, 0,
        0.3,  0.07, 0,
    };

    this->object2 = create3DObject(GL_TRIANGLES, 12, rect_vertex_buffer_data, COLOR_GREY, GL_FILL);

}

void Plank::draw(glm::mat4 VP) 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate_rect = glm::translate (this->position);   
    glm::mat4 rotate_rect    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));    
    rotate_rect          = rotate_rect * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate_rect * rotate_rect);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
}

void Plank::tick()
{
    this->position.x += this->velx;
    return;
}