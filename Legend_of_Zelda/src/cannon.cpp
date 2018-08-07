#include "main.h"
#include "cannon.h"

Cannon::Cannon(float x, float y, float z)
{

    static const GLfloat vertex_buffer_data[] = {
        -2.0f, -2.0f, -2.0f,
        -2.0f, -2.0f,  2.0f,
        -2.0f,  2.0f, -2.0f,

        -2.0f, -2.0f,  2.0f,
        -2.0f,  2.0f, -2.0f,
        -2.0f,  2.0f,  2.0f,

        -2.0f, -2.0f,  2.0f,
        -2.0f, -2.0f, -2.0f,
         2.0f, -2.0f, -2.0f,
        
        -2.0f, -2.0f,  2.0f,
         2.0f, -2.0f, -2.0f,
         2.0f,  2.0f, -2.0f,

         2.0f, -2.0f, -2.0f,
         2.0f, -2.0f,  2.0f,
         2.0f,  2.0f, -2.0f,

         2.0f, -2.0f,  2.0f,
         2.0f,  2.0f, -2.0f,
         2.0f,  2.0f,  2.0f,

         2.0f,  2.0f,  2.0f,
        -2.0f,  2.0f,  2.0f,
         2.0f,  2.0f, -2.0f,

         2.0f,  2.0f, -2.0f,
        -2.0f,  2.0f,  2.0f,
        -2.0f,  2.0f, -2.0f,

        -2.0f,  2.0f,  2.0f,
        -2.0f, -2.0f,  2.0f,
         2.0f,  2.0f,  2.0f,

         2.0f, -2.0f,  2.0f,
        -2.0f, -2.0f,  2.0f,
         2.0f,  2.0f,  2.0f,

        -2.0f,  2.0f, -2.0f,
        -2.0f, -2.0f, -2.0f,
         2.0f,  2.0f, -2.0f,

         2.0f, -2.0f, -2.0f,
        -2.0f, -2.0f, -2.0f,
         2.0f,  2.0f, -2.0f,

    };

    this->theta = 0;
    this->isAlive = 0;
    this->vel = 0;
    this->position = glm::vec3(x, y, z);
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_CANNON, GL_FILL);
}

void Cannon::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate1 = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate = rotate1;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
