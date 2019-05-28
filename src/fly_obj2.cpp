#include "fly_obj2.h"
#include "main.h"

Flyobj2::Flyobj2(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->alive = 1;
    speed = 0.05;
    
    int n=6,i;
    float t=0;
    
    GLfloat vertex_buffer_data1[1000]; 
    GLfloat vertex_buffer_data2[1000];

    for(i=0;i<9*n;i=i+9)
    {    
        vertex_buffer_data1[i]=0.0f;
        vertex_buffer_data1[i+1]=0.0f;
        vertex_buffer_data1[i+2]=-1.0f;

        vertex_buffer_data1[i+3]=0.3f*(sin(2*3.14*t/n));
        vertex_buffer_data1[i+4]=0.3f*(cos(2*3.14*t/n));
        vertex_buffer_data1[i+5]=-1.0f;

        vertex_buffer_data1[i+6]=0.3f*(sin(2*3.14*(t+1)/n));
        vertex_buffer_data1[i+7]=0.3f*(cos(2*3.14*(t+1)/n));
        vertex_buffer_data1[i+8]=-1.0f;
        t=t+1;
        
    };

    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data2[i]=0.0f;
        vertex_buffer_data2[i+1]=0.0f;
        vertex_buffer_data2[i+2]=-1.0f;

        vertex_buffer_data2[i+3]=0.35f*(sin(2*3.14*t/n));
        vertex_buffer_data2[i+4]=0.35f*(cos(2*3.14*t/n));
        vertex_buffer_data2[i+5]=-1.0f;

        vertex_buffer_data2[i+6]=0.35f*(sin(2*3.14*(t+1)/n));
        vertex_buffer_data2[i+7]=0.35f*(cos(2*3.14*(t+1)/n));
        vertex_buffer_data2[i+8]=-1.0f;
        t=t+1;
    };

    this->object1 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data2, COLOR_DARK_BLUE, GL_FILL);    
}

void Flyobj2::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object1);
}

void Flyobj2::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Flyobj2::lefttick() {
    this->position.x -= speed;
}

void Flyobj2::righttick() {
    this->position.x += speed;
}

void Flyobj2::sinetick() {
    this->position.x += 0.01 ;
    this->position.y = sin(this->position.x);
}

bounding_box_t Flyobj2::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.height = 0.35;
    temp.width = 0.35;
    return temp;
}