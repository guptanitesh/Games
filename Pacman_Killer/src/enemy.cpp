#include "enemy.h"
#include "main.h"
#include "plank.h"


Enemy::Enemy(float x,float y) 
{
    color_t color;
    clr=-1;
    if((rand()%20)<2)
    {
        if((rand()%2)==0)
        {
            clr=0;        
            color = COLOR_BLACK;
        }
        else
        {
            clr=1;
            color = COLOR_DGREEN;
        }

    }
    else
    {
        int tp = (int)rand()%4;
        if(tp==0)
            color = COLOR_BLUE;
        else if(tp==1)
            color = COLOR_YELLOW;
        else if(tp==2)
            color = COLOR_PINK;
        else
            color = COLOR_ORANGE;
    }
    if((rand()%8)==0 && clr==-1)
        pl=1;
    else
        pl=0;
    
    // srand(time(NULL));
    x = 4*(((float)rand())/RAND_MAX)+4;
    y = 3*(((float)rand())/RAND_MAX)+0.1;
    flag = 1;
    r=0.4;
    velx=0.02*(((float)rand())/RAND_MAX)+0.01;
    
    if(pl==1)
        ply = Plank(-x-1.5*r, y+0.5*r, 45, velx, COLOR_GREY);

    this->position = glm::vec3(-x, y, 0);
    this->rotation = 0;

    GLfloat vertex_buffer_data[9*360] = {};
    for(int i=0, l=0;i<360;i++)
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

    this->object = create3DObject(GL_TRIANGLES, 3*360, vertex_buffer_data, color, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(this->pl==1)
        this->ply.draw(VP);
}


void Enemy::tick()
{
    if(this->pl==1)
        this->ply.tick();
    this->position[0]+=velx;
    // cout<<this->position[0]<<" "<<this->position[1]<<endl;
    if(this->position[0]>=5)
        this->flag=0;
}

bounding_box_t Enemy::bounding_box()
{
    float x = this->position.x, y = this->position.y, r = this->r;
    bounding_box_t bbox = { x, y, r};
    return bbox;
}
