#include "firebeam.h"
#include "main.h"

Firebeam::Firebeam(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->alive = 1;
    this->killed =0;
    this->speed = 0.1;
    this->speed1 = 0.05;

    int n=1000,i;
    float t=0;

    GLfloat vertex_buffer_data2[100000];
    GLfloat vertex_buffer_data3[100000];
    GLfloat vertex_buffer_data4[100000];
    GLfloat vertex_buffer_data5[100000];

    static const GLfloat vertex_buffer_data1[] = {
        -0.75f,0.20f, -1.0f,
        0.75f, 0.20f, -1.0f,
        0.75f, 0.15f, -1.0f,

        -0.75f, 0.20f, -1.0f,
        0.75f, 0.15f, -1.0f,
        -0.75f, 0.15f, -1.0f,

        -0.75f, -0.15f, -1.0f,
        0.75f, -0.15f, -1.0f,
        0.75f, -0.20f, -1.0f,

        -0.75f, -0.15f, -1.0f,
        0.75f, -0.20f, -1.0f,
        -0.75f, -0.20f, -1.0f
    };

    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data2[i]=0.0f - 0.75f;
        vertex_buffer_data2[i+1]=0.0f + 0.175f;
        vertex_buffer_data2[i+2]=-1.0f;

        vertex_buffer_data2[i+3]=0.1f*(cos(2*3.14*t/n)) - 0.75f;
        vertex_buffer_data2[i+4]=0.1f*(sin(2*3.14*t/n)) + 0.175f;
        vertex_buffer_data2[i+5]=-1.0f;

        vertex_buffer_data2[i+6]=0.1f*(cos(2*3.14*(t+1)/n)) - 0.75;
        vertex_buffer_data2[i+7]=0.1f*(sin(2*3.14*(t+1)/n)) + 0.175f;
        vertex_buffer_data2[i+8]=-1.0f;
        t=t+1;
    };

    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data3[i]=0.0f + 0.75f;
        vertex_buffer_data3[i+1]=0.0f + 0.175f;
        vertex_buffer_data3[i+2]=-1.0f;

        vertex_buffer_data3[i+3]=0.1f*(cos(2*3.14*t/n)) + 0.75f;
        vertex_buffer_data3[i+4]=0.1f*(sin(2*3.14*t/n)) + 0.175f;
        vertex_buffer_data3[i+5]=-1.0f;

        vertex_buffer_data3[i+6]=0.1f*(cos(2*3.14*(t+1)/n)) + 0.75;
        vertex_buffer_data3[i+7]=0.1f*(sin(2*3.14*(t+1)/n)) + 0.175f;
        vertex_buffer_data3[i+8]=-1.0f;
        t=t+1;
    };

        for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data4[i]=0.0f + 0.75f;
        vertex_buffer_data4[i+1]=0.0f - 0.175f;
        vertex_buffer_data4[i+2]=-1.0f;

        vertex_buffer_data4[i+3]=0.1f*(cos(2*3.14*t/n)) + 0.75f;
        vertex_buffer_data4[i+4]=0.1f*(sin(2*3.14*t/n)) - 0.175f;
        vertex_buffer_data4[i+5]=-1.0f;

        vertex_buffer_data4[i+6]=0.1f*(cos(2*3.14*(t+1)/n)) + 0.75;
        vertex_buffer_data4[i+7]=0.1f*(sin(2*3.14*(t+1)/n)) - 0.175f;
        vertex_buffer_data4[i+8]=-1.0f;
        t=t+1;
    };

        for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data5[i]=0.0f - 0.75f;
        vertex_buffer_data5[i+1]=0.0f - 0.175f;
        vertex_buffer_data5[i+2]=-1.0f;

        vertex_buffer_data5[i+3]=0.1f*(cos(2*3.14*t/n)) - 0.75f;
        vertex_buffer_data5[i+4]=0.1f*(sin(2*3.14*t/n)) - 0.175f;
        vertex_buffer_data5[i+5]=-1.0f;

        vertex_buffer_data5[i+6]=0.1f*(cos(2*3.14*(t+1)/n)) - 0.75;
        vertex_buffer_data5[i+7]=0.1f*(sin(2*3.14*(t+1)/n)) - 0.175f;
        vertex_buffer_data5[i+8]=-1.0f;
        t=t+1;
    };

    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data2, COLOR_DARK_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data3, COLOR_DARK_RED, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data4, COLOR_DARK_RED, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data5, COLOR_DARK_RED, GL_FILL);    
}

void Firebeam::draw(glm::mat4 VP) {
    if(this->position.y >= 3) 
    {
        this->speed1 *= -1;
        this->position.y += this->speed1;
    }
    if(this->position.y <= -2) 
    {
        this->speed1 *= -1;
        this->position.y += this->speed1;
    }
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
    draw3DObject(this->object5);
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam::lefttick() {
    this->position.x -= (this->speed) ;
}

void Firebeam::righttick() {
    this->position.x += this->speed ;    
}

void Firebeam::uptick(){
    if (-1 < this->position.y + this->speed1 < 3)
    {
        this->position.y += this->speed1;
    }
}

bounding_box_t Firebeam::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.height = 0.4;
    temp.width = 1.5;
    return temp;
}