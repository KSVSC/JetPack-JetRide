#include "main.h"

#ifndef BALL_H
#define BALL_H

class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    bool alive;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void lefttick();
    void righttick();
    bounding_box_t getboundingbox();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
