#include "main.h"

#ifndef FLYOBJ2_H
#define FLYOBJ2_H

class Flyobj2 {
public:
    Flyobj2() {}
    Flyobj2(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    bool alive;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void lefttick();
    void righttick();
    void sinetick();
    bounding_box_t getboundingbox();
    double speed;
private:
    VAO *object1;
    VAO *object2;
};

#endif // FLYOBJ2_H
