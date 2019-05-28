#include "main.h"
#include "ball.h"

#ifndef WALL_H
#define WALL_H

class Wall {
public:
    Wall() {}
    Wall(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void lefttick();
    void righttick();
    bounding_box_t getboundingbox();
    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // WALL_H
