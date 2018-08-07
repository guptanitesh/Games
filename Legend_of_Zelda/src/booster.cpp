#include "main.h"
#include "booster.h"

Booster::Booster(float x, float y, float z)
{

    GLfloat vertex_buffer_data[360*9*8+10];
    
    float j = -4;
    int r = 2;
    for(int l=0; j+4<8; j+=1)
    for(int i=0; i<360; i++)
    {
        vertex_buffer_data[l++] = j;
        vertex_buffer_data[l++] = r*cos((double)(M_PI*i)/(double)(180));
        vertex_buffer_data[l++] = r*sin((double)(M_PI*i)/(double)(180));

        vertex_buffer_data[l++] = j;
        vertex_buffer_data[l++] = 0.0f;
        vertex_buffer_data[l++] = 0.0f;

        vertex_buffer_data[l++] = j;
        vertex_buffer_data[l++] = r*cos((double)(M_PI*(i+1))/(double)(180));
        vertex_buffer_data[l++] = r*sin((double)(M_PI*(i+1))/(double)(180));
    }

    this->rotation = 0;
    this->position = glm::vec3(x, y, z);
    this->isAlive = 1;
    this->object = create3DObject(GL_TRIANGLES, 8*3*360, vertex_buffer_data, COLOR_BOOSTER, GL_FILL);
}

void Booster::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
