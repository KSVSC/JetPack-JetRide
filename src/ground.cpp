#include "ground.h"
#include "main.h"

Ground::Ground(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.1;

    static const GLfloat vertex_buffer_data[] = {
       
        -100.0f, 0.0f, -1.0f,
        200.0f, 0.0f, -1.0f,
        -100.0f, -3.0f, -1.0f,
        
        -100.0f,-3.0f, -1.0f,
        200.0f, -3.0f, -1.0f,
        200.0f, 0.0f, -1.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ground::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ground::lefttick() {
     this->position.x -= speed;
}

void Ground::righttick() {
     this->position.x += speed;
}

bounding_box_t Ground::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.height = 3;
    temp.width = 300;
    return temp;
}