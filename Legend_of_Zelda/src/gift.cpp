#include "main.h"
#include "gift.h"

Gift::Gift(float x, float y, float z)
{

    GLfloat vertex_buffer_data[360*9+10];

    for(int i=0, l=0, r=3; i<360; i++)
    {
        vertex_buffer_data[l++] = 0.0f;
        vertex_buffer_data[l++] = r*cos((double)(M_PI*i)/(double)(180));
        vertex_buffer_data[l++] = r*sin((double)(M_PI*i)/(double)(180));

        vertex_buffer_data[l++] = 0.0f;
        vertex_buffer_data[l++] = 0.0f;
        vertex_buffer_data[l++] = 0.0f;

        vertex_buffer_data[l++] = 0.0f;
        vertex_buffer_data[l++] = r*cos((double)(M_PI*(i+1))/(double)(180));
        vertex_buffer_data[l++] = r*sin((double)(M_PI*(i+1))/(double)(180));
    }

    this->position = glm::vec3(x, y, z);
    this->isAlive = 1;
    this->rotation = 90;
    this->object = create3DObject(GL_TRIANGLES, 3*360, vertex_buffer_data, COLOR_GIFT, GL_FILL);
}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate1   = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate = rotate1;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
