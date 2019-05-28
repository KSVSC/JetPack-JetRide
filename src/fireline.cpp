#include "fireline.h"
#include "main.h"


Fireline::Fireline(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->alive = 1;
    this->killed = 0;
    speed = 0.1;

    int n=1000,i;
    float t=0;    
    GLfloat vertex_buffer_data2[10000];
    GLfloat vertex_buffer_data3[10000];

    static const GLfloat vertex_buffer_data1[] = {
        -0.5f, 0.35f, -1.0f,
        -0.52f, 0.30f, -1.0f,
        0.48f, -0.30f, -1.0f,

        -0.5f, 0.35f, -1.0f,
        0.48f, -0.30f, -1.0f,
        0.5f, -0.25f, -1.0f
    };
    
    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data2[i]=0.0f - 0.51f;
        vertex_buffer_data2[i+1]=0.0f + 0.325f;
        vertex_buffer_data2[i+2]=-1.0f;

        vertex_buffer_data2[i+3]=0.1f*(cos(2*3.14*t/n)) - 0.51f;
        vertex_buffer_data2[i+4]=0.1f*(sin(2*3.14*t/n)) + 0.325f;
        vertex_buffer_data2[i+5]=-1.0f;

        vertex_buffer_data2[i+6]=0.1f*(cos(2*3.14*(t+1)/n)) - 0.51f;
        vertex_buffer_data2[i+7]=0.1f*(sin(2*3.14*(t+1)/n)) + 0.325f;
        vertex_buffer_data2[i+8]=-1.0f;
        t=t+1;
    };

    for(i=0;i<9*n;i=i+9)
    {
        vertex_buffer_data3[i]=0.0f + 0.49f;
        vertex_buffer_data3[i+1]=0.0f - 0.275f;
        vertex_buffer_data3[i+2]=-1.0f;

        vertex_buffer_data3[i+3]=0.1f*(cos(2*3.14*t/n)) + 0.49f;
        vertex_buffer_data3[i+4]=0.1f*(sin(2*3.14*t/n)) - 0.275f;
        vertex_buffer_data3[i+5]=-1.0f;

        vertex_buffer_data3[i+6]=0.1f*(cos(2*3.14*(t+1)/n)) + 0.49f;
        vertex_buffer_data3[i+7]=0.1f*(sin(2*3.14*(t+1)/n)) - 0.275f;
        vertex_buffer_data3[i+8]=-1.0f;
        t=t+1;
    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data3, COLOR_YELLOW, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireline::lefttick() {
     this->position.x -= speed; 
}

void Fireline::righttick() {
     this->position.x += speed;
}

bounding_box_t Fireline::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.height = 0.65;
    temp.width = 1.02;
    return temp;
}