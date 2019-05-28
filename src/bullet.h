#include "main.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    bool alive;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    double xspeed;
    void righttick();
    bounding_box_t getboundingbox();
private:
    VAO *object;
};

#endif // BULLET_H
