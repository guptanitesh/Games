#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x,float y,color_t color, int flag)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    GLfloat vertex_buffer_data1[] = {
        3.5, 3, 0,
        3.5, 4, 0,
        3.75, 3, 0,

        3.5, 4, 0,
        3.75, 3, 0,
        3.75, 4, 0,
        
        3.75, 3, 0,
        3.75, 2.75, 0,
        2.5, 3, 0,

        3.75, 2.75, 0,
        2.5, 3, 0,
        2.5, 2.75, 0,

        3.75, 4, 0,
        3.75, 4.25, 0,
        2.5, 4, 0,

        3.75, 4.25, 0,
        2.5, 4, 0,
        2.5, 4.25, 0
    };

    GLfloat vertex_buffer_data2[] = {
        -3.5, 3, 0,
        -3.5, 4, 0,
        -3.75, 3, 0,
           
        -3.5, 4, 0,
        -3.75, 3, 0,
        -3.75, 4, 0,
        
        -3.75, 3, 0,
        -3.75, 2.75, 0,
        -2.5, 3, 0,

        -3.75, 2.75, 0,
        -2.5, 3, 0,
        -2.5, 2.75, 0,

        -3.75, 4, 0,
        -3.75, 4.25, 0,
        -2.5, 4, 0,

        -3.75, 4.25, 0,
        -2.5, 4, 0,
        -2.5, 4.25, 0
    };
    if(flag==1)
        this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data1, color, GL_FILL);
    else
        this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data2, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

