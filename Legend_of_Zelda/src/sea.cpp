#include "main.h"
#include "sea.h"

Sea::Sea(float y)
{
    GLfloat vertex_buffer_data[360*9+10];

    for(int i=0,l=0,r=INT_MAX; i<360; i++)
    {
        vertex_buffer_data[l++] = r*cos((double)(M_PI*i)/(double)(180));
        vertex_buffer_data[l++] = 0.0f;
        vertex_buffer_data[l++] = r*sin((double)(M_PI*i)/(double)(180));

        vertex_buffer_data[l++] = 0.0f;
        vertex_buffer_data[l++] = 0.0f;
        vertex_buffer_data[l++] = 0.0f;

        vertex_buffer_data[l++] = r*cos((double)(M_PI*(i+1))/(double)(180));
        vertex_buffer_data[l++] = 0.0f;
        vertex_buffer_data[l++] = r*sin((double)(M_PI*(i+1))/(double)(180));
    }

    this->position = glm::vec3(0, y, 0);
    this->object = create3DObject(GL_TRIANGLES, 3*360, vertex_buffer_data, COLOR_SEA, GL_FILL);
}

void Sea::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate = glm::rotate((float) (0.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
