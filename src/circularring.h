#include "main.h"

#ifndef CIRCULARRING_H
#define CIRCULARRING_H

class Circularring {
public:
    Circularring() {}
    Circularring(float x, float y, color_t color);
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
    VAO *object1;
    VAO *object2;
};

#endif // CIRCULARRING_H
