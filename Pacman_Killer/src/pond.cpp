#include "pond.h"
#include "main.h"
#include <math.h>

Pond::Pond(float x, float y, color_t color) 
{
    r = 1.25;
    int l=0;
    this->rotation = 0;
    this->position = glm::vec3(x, y, 0);
    GLfloat vertex_buffer_data[9*180] = {};
    for(int i=180;i<360;i++)
    {
        vertex_buffer_data[l++] = 0;
        vertex_buffer_data[l++] = 0;
        vertex_buffer_data[l++] = 0;
        
        vertex_buffer_data[l++] = r*cos((double)(M_PI*i)/(double)(180));
        vertex_buffer_data[l++] = r*sin((double)(M_PI*i)/(double)(180));
        vertex_buffer_data[l++] = 0;

        vertex_buffer_data[l++] = r*cos((double)(M_PI*(i+1))/(double)(180));
        vertex_buffer_data[l++] = r*sin((double)(M_PI*(i+1))/(double)(180));
        vertex_buffer_data[l++] = 0;

    }
    this->object = create3DObject(GL_TRIANGLES, l/3, vertex_buffer_data, color, GL_FILL);
}

   
void Pond::draw(glm::mat4 VP)
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


bounding_box_t Pond::bounding_box()
{
    float x = this->position.x, y = this->position.y, r = this->r;
    bounding_box_t bbox = { x, y, r};
    return bbox;
}
