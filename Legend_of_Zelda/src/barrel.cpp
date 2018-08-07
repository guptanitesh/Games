#include "barrel.h"
#include "main.h"

Barrel::Barrel(float y)
{
    int tpx1, tpx2, tpz1, tpz2;
    tpx1 = (rand() % 3500) + 200;
    tpz1 = (rand() % 3500) + 200;
    tpx2 = (-1)*(rand() % 3500) - 200;
    tpz2= (-1)*(rand() % 3500) - 200;
    if(rand()%2)
        tpx1 = tpx2;
    if(rand()%2)
        tpz1 = tpz2;

    this->position = glm::vec3(tpx1, y, tpz1);
    this->rotation = 0;
    float j = -10;
    int r = 5;
    GLfloat vertex_buffer_data[360*9*20+10];
    for(int l=0; j+10<20; j+=1)
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

    GLfloat vertex_buffer_data2[] = {
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

    for(int i = 0; i<9*12; i++)
        if(i%3 == 1)
            vertex_buffer_data2[i] += 2*r;

    this->object = create3DObject(GL_TRIANGLES, 20*3*360, vertex_buffer_data, COLOR_BARREL, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 32, vertex_buffer_data2, COLOR_COIN, GL_FILL);

}

void Barrel::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}
