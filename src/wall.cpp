#include "wall.h"
#include "main.h"

Wall::Wall(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.1;

    static const GLfloat vertex_buffer_data[] = {
        //first vert
        0.25f, 1.0f,-1.0f, 
        -0.25f,-2.0f,-1.0f,
        -0.25f, 1.0f,-1.0f,
        0.25f, 1.0f,-1.0f,
        0.25f,-2.0f,-1.0f,
        -0.25f,-2.0f,-1.0f,
        //first hor
        0.25f, 1.0f,-1.0f,
        0.25f, 0.5f,-1.0f,
        2.75f, 1.0f,-1.0f,
        2.75f, 1.0f,-1.0f,
        0.25f, 0.5f,-1.0f,
        2.75f, 0.5f,-1.0f,
        //second vert
        3.25f, 1.0f,-1.0f, 
        2.75f,-2.0f,-1.0f,
        2.75f, 1.0f,-1.0f,
        3.25f, 1.0f,-1.0f,
        3.25f,-2.0f,-1.0f,
        2.75f,-2.0f,-1.0f,
        //second hor
        0.25f, -1.5f,-1.0f,
        0.25f, -2.0f,-1.0f,
        2.75f, -1.5f,-1.0f,
        2.75f, -1.5f,-1.0f,
        0.25f, -2.0f,-1.0f,
        2.75f, -2.0f,-1.0f,
    };

    static const GLfloat vertex_buffer_data1[]={
        0.25f, 0.5f, -1.0f,
        2.75f, 0.5f, -1.0f,
        1.5f, -0.5f, -1.0f,

        1.5f, -0.5f, -1.0f,
        2.75f, -1.5f, -1.0f,        
        0.25f, -1.5f, -1.0f
    };

    static const GLfloat vertex_buffer_data2[]={
        1.5f, -0.5f, -1.0f,
        2.75f, -1.5f, -1.0f,        
        2.75f, 0.5f, -1.0f,

        0.25f, -1.5f, -1.0f,
        1.5f, -0.5f, -1.0f,
        0.25f, 0.5f, -1.0f
    };    

    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_LIGHT_BLUE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_GREEN, GL_FILL);
}

void Wall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Wall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Wall::lefttick() {
     this->position.x -= speed;
}

void Wall::righttick() {
     this->position.x += speed;
}

bounding_box_t Wall::getboundingbox() {

    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.height = 3;
    temp.width = 3.25;
    return temp;
}