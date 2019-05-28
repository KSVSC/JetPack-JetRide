#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H

class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    bool alive;
    bool killed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void lefttick();
    void righttick();
    bounding_box_t getboundingbox();
    double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // FIRELINE_H
