#include "bomerang.h"
#include "main.h"


Bomerang::Bomerang(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->alive = 1;
    this->t = 0;
    this->x = this->position.x;
    this->y = this->position.y;
    speed = 0.1;

    int n=5,i;
    float t=0;    
    GLfloat vertex_buffer_data[10000];
    GLfloat vertex_buffer_data1[10000];
    
    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data[i]=0.0f;
        vertex_buffer_data[i+1]=0.0f;
        vertex_buffer_data[i+2]=-1.0f;

        vertex_buffer_data[i+3]=0.35f*(cos(2*3.14*t/n));
        vertex_buffer_data[i+4]=0.35f*(sin(2*3.14*t/n));
        vertex_buffer_data[i+5]=-1.0f;

        vertex_buffer_data[i+6]=0.35f*(cos(2*3.14*(t+1)/n));
        vertex_buffer_data[i+7]=0.35f*(sin(2*3.14*(t+1)/n));
        vertex_buffer_data[i+8]=-1.0f;
        t=t+1;
    };

    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data1[i]=0.0f;
        vertex_buffer_data1[i+1]=0.0f;
        vertex_buffer_data1[i+2]=-1.0f;

        vertex_buffer_data1[i+3]=0.25f*(cos(2*3.14*t/n));
        vertex_buffer_data1[i+4]=0.25f*(sin(2*3.14*t/n));
        vertex_buffer_data1[i+5]=-1.0f;

        vertex_buffer_data1[i+6]=0.25f*(cos(2*3.14*(t+1)/n));
        vertex_buffer_data1[i+7]=0.25f*(sin(2*3.14*(t+1)/n));
        vertex_buffer_data1[i+8]=-1.0f;
        t=t+1;
    };

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_DARK_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data1, color, GL_FILL);
}

void Bomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Bomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bomerang::lefttick() {
     this->position.x -= speed;
     this->x -= speed; 
}

void Bomerang::righttick() {
     this->position.x += speed;
     this->x += speed;
}

void Bomerang::tick(){
    int n = 100;
    if(t<=100)
    {
        this->position.x= this->x - (3.0f*(sin(3.14*t/n)));
        this->position.y= this->y + 1.15f*(cos(3.14*t/n));
        t ++;
    }
    else
    {
        t = 0;
    }
}

bounding_box_t Bomerang::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x-0.3;
    temp.y = this->position.y+0.3;
    temp.height = 0.35;
    temp.width = 0.35;
    return temp;
}