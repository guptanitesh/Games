#include "ball.h"
#include "main.h"
#include <math.h>

Ball::Ball(float x, float y, color_t color) 
{
    velx=0;vely=0;ax=0;ay=0;
    r = 0.4;
    y+=r;
    this->rotation = 0;
    this->position = glm::vec3(x, y, 0);
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

   
void Ball::draw(glm::mat4 VP)
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

void Ball::tick()
{
    if(((this->position.x)<-2.25 || (this->position.x)>0.25) || (this->position.y-this->r>=-1))
    {
        this->position.y+=this->vely;
        this->position.x+=this->velx;
        this->velx+=this->ax;
        this->vely+=this->ay;
        if(this->position.x+this->r>4)
            this->position.x=4-this->r;
        if(this->position.x-this->r<-4)
            this->position.x=-4+this->r;
        if(this->position.y-this->r <= -1)
        {
            this->position.y=this->r-1;;
            this->vely=0;
            this->ay=0;
        }
    }
    else
    {
        double tp3=-sqrt(abs((1.25-this->r)*(1.25-this->r)-(this->position.x+1)*(this->position.x+1)))-1;
        // cout<<"val"<<tp3-this->position.y<<endl;
        if(abs(tp3-this->position.y)<=0.2)
        {
            // cout<<"here"<<this->vely<<" "<<this->ay<<endl;
            if(this->vely>0)
            {
                this->position.y+=vely;
                this->vely+=this->ay;
            }
            else
            {
                // if(abs(tp3-this->position.y)<0.05)
                    this->position.y=tp3;
                // else
                // {
                //     cout<<"Here"<<endl;
                //     if(tp3>this->position.y)
                //         this->position.y+=0.05;
                //     else
                //         this->position.y-=0.05;
                // }
                if(abs(this->position.x+1)>0.01)
                {
                    if(this->position.x<-1)
                        this->position.x+=0.01;
                    else
                        this->position.x-=0.01;
                }
                // tp3=-sqrt(abs((1.25-this->r)*(1.25-this->r)-(this->position.x+1)*(this->position.x+1)))-1;

            }
        }
        else
        {
            // cout<<"There"<<this->vely<<" "<<this->ay<<endl;
            if(this->vely>0)
            {
                this->position.y+=vely;
                this->vely+=this->ay;
            }
            else
            {

                // this->position.y-=0.001;
            }
        }
    }
}

bounding_box_t Ball::bounding_box()
{
    float x = this->position.x, y = this->position.y, r = this->r;
    bounding_box_t bbox = { x, y, r};
    return bbox;
}
