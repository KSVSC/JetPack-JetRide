#include "fly_obj3.h"
#include "main.h"

Flyobj3::Flyobj3(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->alive = 1;
    speed = 0.05;
    
    static const GLfloat vertex_buffer_data[]={
        0.0f, -0.5f, -1.0f,
        -0.45f, 0.0f, -1.0f,
        0.45f, 0.0f, -1.0f,

        0.45f, 0.0f, -1.0f,
        0.3f, 0.35f, -1.0f,
        0.0f, 0.0f ,-1.0f,

        0.3f, 0.35f, -1.0f,
        0.0f, 0.0f ,-1.0f,
        0.1f, 0.35f, -1.0f,

        -0.45f, 0.0f, -1.0f,
        -0.3f, 0.35f, -1.0f,
        0.0f, 0.0f ,-1.0f,

        -0.3f, 0.35f, -1.0f,
        0.0f, 0.0f ,-1.0f,
        -0.1f, 0.35f, -1.0f        
    };

    static const GLfloat vertex_buffer_data1[]={
        -0.45f, 0.35f, -1.0f,
        0.45f, 0.35f, -1.0f,
        0.45f, -0.5f, -1.0f,

        -0.45f, 0.35f, -1.0f,
        0.45f, -0.5f, -1.0f,
        -0.45f, -0.5f, -1.0f,                        
    };


    this->object = create3DObject(GL_TRIANGLES, 5*3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_RED, GL_FILL);    
}

void Flyobj3::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object);
}

void Flyobj3::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Flyobj3::lefttick() {
    this->position.x -= speed;
}

void Flyobj3::righttick() {
    this->position.x += speed;
}

void Flyobj3::costick() {
    this->position.x += 0.01 ;
    this->position.y = cos(this->position.x);
}

bounding_box_t Flyobj3::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.height = 0.85;
    temp.width = 0.9;
    return temp;
}