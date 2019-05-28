#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->alive = 1;
    speed = 0.1;

    static const GLfloat vertex_buffer_data[] = {
        
        0.25f, 0.25f,-1.0f, // triangle 2 : begin
        -0.25f, 0.0f,-1.0f,
        -0.25f, 0.25f,-1.0f, // triangle 2 : end
        
        0.25f, 0.25f,-1.0f,
        0.25f, 0.0f,-1.0f,
        -0.25f, 0.0f,-1.0f,
        
         0.25f, 0.25f,-1.0f,
        0.25f, 0.0f,-1.0f,
        0.5f, 0.25f,-1.0f,
        
        0.25f, 0.0f,-1.0f,
        0.5f, 0.25f,-1.0f,
        0.5f, 0.0f,-1.0f,
        
        0.25f, 0.0f,-1.0f,
        0.5f, 0.0f,-1.0f,
        0.5f,-0.25f,-1.0f,
        
        0.5f,-0.25f,-1.0f,
        0.25f, 0.0f,-1.0f,
        0.25f, -0.25f,-1.0f,
        
        0.25f, -0.25f,-1.0f,
        0.5f, -0.25f,-1.0f,
        0.5f, -0.5f,-1.0f,
        
        0.25f, -0.5f,-1.0f,
        0.25f, -0.25f,-1.0f,
        0.5f, -0.5f,-1.0f,
        
        0.25f, -0.25f, -1.0f,
        0.25f, -0.5f, -1.0f,
        -0.25f, -0.5f, -1.0f,
        
        0.25f, -0.25f, -1.0f,
        -0.25f, -0.5f, -1.0f,
        -0.25f, -0.25f, -1.0f
        
    };

    this->object = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::lefttick() {
     this->position.x -= speed;
}

void Magnet::righttick() {
     this->position.x += speed;
}

bounding_box_t Magnet::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x - 1.5;
    temp.y = this->position.y;
    temp.height = 0.75;
    temp.width = 0.75;
    return temp;
}

void Magnet::disappear(){
    if(this->alive == 0)
        this->alive = 1;
    else
        this->alive = 0;
}