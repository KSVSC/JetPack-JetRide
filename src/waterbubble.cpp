#include "waterbubble.h"
#include "main.h"
#include "player.h"

Waterbubble::Waterbubble(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->alive = 0;
    xspeed = 0.05;
    yspeed = 0;
    gravity = -0.07;
    int n=1000,i;
    float t=0;

    GLfloat vertex_buffer_data[100000];
     
    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data[i]=0.0f;
        vertex_buffer_data[i+1]=0.0f;
        vertex_buffer_data[i+2]=0.0f;

        vertex_buffer_data[i+3]=0.15f*(cos(2*3.14*t/n));
        vertex_buffer_data[i+4]=0.15f*(sin(2*3.14*t/n));
        vertex_buffer_data[i+5]=0.0f;

        vertex_buffer_data[i+6]=0.15f*(cos(2*3.14*(t+1)/n));
        vertex_buffer_data[i+7]=0.15f*(sin(2*3.14*(t+1)/n));
        vertex_buffer_data[i+8]=0.0f;
        t=t+1;
    };

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Waterbubble::draw(glm::mat4 VP) {
    if(this->up)
        this->lefttick();
    if(!this->up)
        this->righttick();    
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Waterbubble::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Waterbubble::righttick() {
     this->position.x += xspeed;
     this->yspeed += gravity;
     this->position.y += yspeed;
}

void Waterbubble::lefttick() {
     this->position.x += xspeed;
     this->yspeed -= gravity;
     this->position.y += yspeed;
}

bounding_box_t Waterbubble::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.height = 0.15;
    temp.width = 0.15;
    return temp;
}