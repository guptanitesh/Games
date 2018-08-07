#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z)
{

    static const GLfloat vertex_buffer_data1[] = {
        -7.0f,-2.0f, 5.0f,
         7.0f, 2.0f, 4.0f,
        -7.0f, 2.0f, 5.0f,

        -7.0f,-2.0f, 5.0f,
         7.0f, 2.0f, 4.0f,
         7.0f,-2.0f, 4.0f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, COLOR_RED, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {
         7.0f, 2.0f, 4.0f,
         7.0f,-2.0f,-4.0f,
         7.0f,-2.0f, 4.0f,
         
         7.0f, 2.0f, 4.0f,
         7.0f,-2.0f,-4.0f,
         7.0f, 2.0f,-4.0f,
    };
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_GREEN, GL_FILL);

    static const GLfloat vertex_buffer_data3[] = {
         7.0f, 2.0f,-4.0f,
        -7.0f,-2.0f,-5.0f,
         7.0f,-2.0f,-4.0f,
         
         7.0f, 2.0f,-4.0f,
        -7.0f,-2.0f,-5.0f,
        -7.0f, 2.0f,-5.0f,
    };
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, COLOR_GREY, GL_FILL);

    static const GLfloat vertex_buffer_data4[] = {
        -7.0f,-2.0f,-5.0f,
        -7.0f, 2.0f, 5.0f,
        -7.0f, 2.0f,-5.0f,
        
        -7.0f,-2.0f,-5.0f,
        -7.0f, 2.0f, 5.0f,
        -7.0f,-2.0f, 5.0f,
    };
    this->object4 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data4, COLOR_DGREEN, GL_FILL);

    static const GLfloat vertex_buffer_data5[] = {
        -7.0f,-2.0f, 5.0f,
         7.0f,-2.0f,-4.0f,
         7.0f,-2.0f, 4.0f,
        
        -7.0f,-2.0f, 5.0f,
         7.0f,-2.0f,-4.0f,
        -7.0f,-2.0f,-5.0f,
    };
    this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data5, COLOR_YELLOW, GL_FILL);

    static const GLfloat vertex_buffer_data6[] = {
         7.0f, 2.0f, 4.0f,
         7.0f,-2.0f, 4.0f,
        14.0f, 3.0f, 0.0f,

         7.0f,-2.0f, 4.0f,
         7.0f,-2.0f,-4.0f,
        14.0f, 3.0f, 0.0f,

         7.0f,-2.0f,-4.0f,
         7.0f, 2.0f,-4.0f,
        14.0f, 3.0f, 0.0f,

         7.0f, 2.0f,-4.0f,
         7.0f, 2.0f, 4.0f,
        14.0f, 3.0f, 0.0f,
    };
    // this->object6 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data6, COLOR_BLACK, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data6, COLOR_ORANGE, GL_FILL);

    float j = 14, r = 0.5;
    GLfloat vertex_buffer_data9[360*9*20+10];
    for(int l=0; j<24; j+=0.5)
    for(int i=0; i<360; i++)
    {
        vertex_buffer_data9[l++] = j;
        vertex_buffer_data9[l++] = 3 + r*cos((double)(M_PI*i)/(double)(180));
        vertex_buffer_data9[l++] = r*sin((double)(M_PI*i)/(double)(180));

        vertex_buffer_data9[l++] = j;
        vertex_buffer_data9[l++] = 3.0f;
        vertex_buffer_data9[l++] = 0.0f;

        vertex_buffer_data9[l++] = j;
        vertex_buffer_data9[l++] = 3 + r*cos((double)(M_PI*(i+1))/(double)(180));
        vertex_buffer_data9[l++] = r*sin((double)(M_PI*(i+1))/(double)(180));
    }
    this->object9 = create3DObject(GL_TRIANGLES, 20*3*360, vertex_buffer_data9, COLOR_BLACK, GL_FILL);


    static const GLfloat vertex_buffer_data7[] = {
        5.0f, -2.0f, 0.5f,
        5.0f,-2.0f, 0.0f,
        5.0f, 20.0f, 0.5f,

        5.0f,-2.0f, 0.0f,
        5.0f, 20.0f, 0.5f,
        5.0f, 20.0f, 0.0f,
    };
    this->object7 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data7, COLOR_PINK, GL_FILL);

    static const GLfloat vertex_buffer_data8[] = {
        5.5f,18.0f, 0.0f,
        5.5f, 9.0f, 0.0f,
        5.5f, 9.0f,-5.5f,

        5.5f,18.0f, 0.0f,
        5.5f, 9.0f,-5.5f,
        5.5f,18.0f,-5.5f,

        5.5f,18.0f, 0.5f,
        5.5f, 9.0f, 0.5f,
        5.5f, 9.0f, 6.0f,

        5.5f,18.0f, 0.5f,
        5.5f,18.0f, 6.0f,
        5.5f, 9.0f, 6.0f,
    };
    this->object8 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data8, COLOR_BLACK, GL_FILL);

    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->vel = 4;
    this->vely = 0;
    this->g = 0;
    this->omega = 0.25;
    this->vel_y = 0.02;
    this->ltheta = 0;
    this->ay = -0.0001;



}

void Boat::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate1 = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2 = glm::rotate((float) (this->ltheta * M_PI / 180.0f), glm::vec3(this->position.x, this->position.y, this->position.z - 2));
    glm::mat4 rotate = rotate1 * rotate2;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object9);
    draw3DObject(this->object8);
    draw3DObject(this->object7);
    draw3DObject(this->object6);
    draw3DObject(this->object5);
    draw3DObject(this->object4);
    draw3DObject(this->object3);
    draw3DObject(this->object2);
    draw3DObject(this->object1);
}
