#include "fly_obj.h"
#include "main.h"

Flyobj::Flyobj(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->alive = 1;
    speed = 0.05;

    static const GLfloat vertex_buffer_data1[] = {
        
        -0.25f, -0.25f, -1.0f,
        -0.25f, 0.25f, -1.0f,
        0.25f, 0.0f, -1.0f
        
    };

    static const GLfloat vertex_buffer_data2[] = {
        
        -0.3f, -0.65f, -1.0f,
        -0.3f, 0.65f, -1.0f,
        0.3f, 0.0f, -1.0f
        
    };

    this->object1 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data2, COLOR_GREEN, GL_FILL);    
}

void Flyobj::draw(glm::mat4 VP) {
    if(this->position.y >= 3) 
    {
        this->speed *= -1;
        this->position.y += this->speed;
    }
    if(this->position.y <= -1) 
    {
        this->speed *= -1;
        this->position.y += this->speed;
    }
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object1);
}

void Flyobj::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Flyobj::lefttick() {
    this->position.x -= (this->speed + 0.02) ;
    if (-1 < this->position.y + this->speed < 3)
    {
        this->position.y += this->speed;
    }

}

void Flyobj::righttick() {
    this->position.x += 0.15 ;
    if (-1 < this->position.y + this->speed < 3)
    {
        this->position.y += this->speed;
    }
}

void Flyobj::slowtick() {
    this->position.x += 0.01 ;
    if (-1 < this->position.y + this->speed < 3)
    {
        this->position.y += this->speed;
    }
}

bounding_box_t Flyobj::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.height = 1.3;
    temp.width = 0.6;
    return temp;
}