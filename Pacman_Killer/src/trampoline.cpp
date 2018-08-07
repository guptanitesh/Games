#include "trampoline.h"
#include "main.h"

Trampoline::Trampoline(float x,float y,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    l=0;
    GLfloat vertex_buffer_data[1800] = {};
    GLfloat tp[] = {
        2, -1, 0,
        2, 0, 0,
        2.125,-1, 0,

        2, 0, 0,
        2.125, 0, 0, 
        2.125, -1, 0, 

        3.125, -1, 0,
        3.125, 0, 0,
        3.25,-1, 0,

        3.125, 0, 0,
        3.25, 0, 0, 
        3.25, -1, 0 
    };

    for(int i=180;i<360;i++)
    {
        vertex_buffer_data[l++] = 2.625;
        vertex_buffer_data[l++] = 0;
        vertex_buffer_data[l++] = 0;
        
        vertex_buffer_data[l++] = 2.625+0.5*cos((double)(M_PI*i)/(double)(180));
        vertex_buffer_data[l++] = 0.5*sin((double)(M_PI*i)/(double)(180));
        vertex_buffer_data[l++] = 0;

        vertex_buffer_data[l++] = 2.625+0.5*cos((double)(M_PI*(i+1))/(double)(180));
        vertex_buffer_data[l++] = 0.5*sin((double)(M_PI*(i+1))/(double)(180));
        vertex_buffer_data[l++] = 0;
    }

    for(int i=0;i<36;i++)
        vertex_buffer_data[l++] = tp[i];

    beg=2;
    end=3.25;
    top=0;
    this->object = create3DObject(GL_TRIANGLES, l/3, vertex_buffer_data, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

