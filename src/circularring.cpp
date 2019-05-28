#include "circularring.h"
#include "main.h"


Circularring::Circularring(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->alive = 1;
    speed = 0.1;

    int n=1000,i;
    float t=0;    
    GLfloat vertex_buffer_data1[10000];
    GLfloat vertex_buffer_data2[10000];
   
    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data1[i]=0.0f;
        vertex_buffer_data1[i+1]=0.0f;
        vertex_buffer_data1[i+2]=-1.0f;

        vertex_buffer_data1[i+3]=1.5f*(sin(3.14*t/n));
        vertex_buffer_data1[i+4]=1.5f*(cos(3.14*t/n));
        vertex_buffer_data1[i+5]=-1.0f;

        vertex_buffer_data1[i+6]=1.5f*(sin(3.14*(t+1)/n));
        vertex_buffer_data1[i+7]=1.5f*(cos(3.14*(t+1)/n));
        vertex_buffer_data1[i+8]=-1.0f;
        t=t+1;
    };

    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data2[i]=0.0f;
        vertex_buffer_data2[i+1]=0.0f;
        vertex_buffer_data2[i+2]=-1.0f;

        vertex_buffer_data2[i+3]=-1.35f*(sin(3.14*t/n));
        vertex_buffer_data2[i+4]=1.35f*(cos(3.14*t/n));
        vertex_buffer_data2[i+5]=-1.0f;

        vertex_buffer_data2[i+6]=-1.35f*(sin(3.14*(t+1)/n));
        vertex_buffer_data2[i+7]=1.35f*(cos(3.14*(t+1)/n));
        vertex_buffer_data2[i+8]=-1.0f;
        t=t+1;
    };

    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data2, COLOR_BACKGROUND, GL_FILL);
}

void Circularring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Circularring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Circularring::lefttick() {
     this->position.x -= speed; 
}

void Circularring::righttick() {
     this->position.x += speed;
}

bounding_box_t Circularring::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x-0.3;
    temp.y = this->position.y+0.3;
    temp.height = 0.15;
    temp.width = 0.15;
    return temp;
}