#include "viserion.h"
#include "main.h"

Viserion::Viserion(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.1;

    int n2=6,n3=4,n4=1000,i;
    float t2=0,t3=0,t4=0;

    GLfloat vertex_buffer_data2[100000];
    GLfloat vertex_buffer_data3[100000];
    GLfloat vertex_buffer_data4[100000];
   
     static const GLfloat vertex_buffer_data1[] = {
        0.05, 0.3, -1,
        0.0,  0.0, -1,
        0.1,  0.0, -1,

        0.15,  0.3, -1,
        0.1, 0.0, -1, 
        0.2, 0.0, -1, 

        -0.05, 0.3,-1,
        0.0, 0.0, -1,
        -0.1, 0.0, -1,

        -0.15,  0.3, -1,
        -0.1, 0.0, -1,
        -0.2, 0.0, -1 
    };

    for(i=0;i<9*n2;i=i+9)
    {
        vertex_buffer_data2[i]=0.0f;
        vertex_buffer_data2[i+1]=-0.2f;
        vertex_buffer_data2[i+2]=-1.0f;

        vertex_buffer_data2[i+3]=0.3f*(cos(2*3.14*t2/n2));
        vertex_buffer_data2[i+4]=0.3f*(sin(2*3.14*t2/n2)) - 0.2f;
        vertex_buffer_data2[i+5]=-1.0f;

        vertex_buffer_data2[i+6]=0.3f*(cos(2*3.14*(t2+1)/n2));
        vertex_buffer_data2[i+7]=0.3f*(sin(2*3.14*(t2+1)/n2)) - 0.2;
        vertex_buffer_data2[i+8]=-1.0f;
        t2=t2+1;
    };

    for(i=0;i<9*n3;i=i+9)
    {
        vertex_buffer_data3[i]=0.0f;
        vertex_buffer_data3[i+1]=-0.75f;
        vertex_buffer_data3[i+2]=-1.0f;

        vertex_buffer_data3[i+3]=0.4f*((1/1.414)*cos(2*3.14*t3/n3)-(1/1.414)*(sin(2*3.14*t3/n3)));
        vertex_buffer_data3[i+4]=0.4f*((1/1.414)*cos(2*3.14*t3/n3)+(1/1.414)*(sin(2*3.14*t3/n3))) - 0.75f;
        vertex_buffer_data3[i+5]=-1.0f;

        vertex_buffer_data3[i+6]=(0.4f*(cos(2*3.14*(t3+1)/n3))*(1/1.414))-((0.4f*(sin(2*3.14*(t3+1)/n3)))*(1/1.414));
        vertex_buffer_data3[i+7]=(0.4f*(cos(2*3.14*(t3+1)/n3))*(1/1.414))+((0.4f*(sin(2*3.14*(t3+1)/n3)))*(1/1.414)) - 0.75f;
        vertex_buffer_data3[i+8]=-1.0f;
        t3=t3+1;
    };

    for(i=0;i<9*n4;i=i+9)
    {
        vertex_buffer_data4[i]=0.2f;
        vertex_buffer_data4[i+1]=-0.2f;
        vertex_buffer_data4[i+2]=-1.0f;

        vertex_buffer_data4[i+3]=0.05f*(cos(2*3.14*t4/n4)) +0.2f;
        vertex_buffer_data4[i+4]=0.05f*(sin(2*3.14*t4/n4)) -0.2f;
        vertex_buffer_data4[i+5]=-1.0f;

        vertex_buffer_data4[i+6]=0.05f*(cos(2*3.14*(t4+1)/n4)) +0.2f;
        vertex_buffer_data4[i+7]=0.05f*(sin(2*3.14*(t4+1)/n4)) - 0.2f;
        vertex_buffer_data4[i+8]=-1.0f;
        t4=t4+1;
    };

    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data1, COLOR_DARK_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n2*3, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, n3*3, vertex_buffer_data3, COLOR_DARK_RED, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, n4*3, vertex_buffer_data4, COLOR_YELLOW, GL_FILL);
}

void Viserion::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Viserion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Viserion::lefttick() {
    this->position.x -= (this->speed) ;
}