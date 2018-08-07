#include "main.h"
#include "monster.h"

Monster::Monster(float y)
{
    int tp = rand()%360;
    this->rotation = 90;

    if (rand()%2)
        this->rotation += tp;
    else
        this->rotation -= tp;

    int tpx1, tpx2, tpz1, tpz2;
    tpx1 = (rand() % 500) + 100;
    tpz1 = (rand() % 500) + 100;
    tpx2 = (-1)*(rand() % 500) - 100;
    tpz2= (-1)*(rand() % 500) - 100;
    if(rand()%2)
        tpx1 = tpx2;
    if(rand()%2)
        tpz1 = tpz2;


    GLfloat vertex_buffer_data[2*9*20] = {};

    float diff = (float)(2*M_PI)/(float)(20), theta = 0;

    for(int i=0, l=0, r=8; i<20; i++)
    {
        vertex_buffer_data[l++] = r*cos(theta);
        vertex_buffer_data[l++] =  0.0f;
        vertex_buffer_data[l++] = r*sin(theta);

        vertex_buffer_data[l++] = 0.0;
        vertex_buffer_data[l++] = 10.0; 
        vertex_buffer_data[l++] = 0.0f;
        

        theta+= diff;
        vertex_buffer_data[l++]=r*cos(theta);
        vertex_buffer_data[l++]= 0.0f;
        vertex_buffer_data[l++]=r*sin(theta);

        theta-= diff;
        vertex_buffer_data[l++] = r*cos(theta);
        vertex_buffer_data[l++] =  0.0f;
        vertex_buffer_data[l++] = r*sin(theta);
        
        vertex_buffer_data[l++] = 0.0;
        vertex_buffer_data[l++] = -10.0; 
        vertex_buffer_data[l++] = 0.0f;

        theta+= diff;
        vertex_buffer_data[l++]=r*cos(theta);
        vertex_buffer_data[l++]= 0.0f;
        vertex_buffer_data[l++]=r*sin(theta);
    }


    this->isAlive = 1;
    this->position = glm::vec3(tpx1, y, tpz1);
    this->vel = 2;
    tp = rand()%3;
    if(tp == 0)
        this->object = create3DObject(GL_TRIANGLES, 6*20, vertex_buffer_data, COLOR_MONSTER, GL_FILL);
    else if(tp == 1)
        this->object = create3DObject(GL_TRIANGLES, 6*20, vertex_buffer_data, COLOR_MONSTERR, GL_FILL);
    else
        this->object = create3DObject(GL_TRIANGLES, 6*20, vertex_buffer_data, COLOR_MONSTERRR, GL_FILL);
}

void Monster::draw(glm::mat4 VP)
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
