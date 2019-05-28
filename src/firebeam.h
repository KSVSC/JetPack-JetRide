#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H

class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    bool killed;
    bool alive;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void lefttick();
    void righttick();
    void uptick();
    bounding_box_t getboundingbox();
    double speed;
    double speed1;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
};

#endif // FIREBEAM_H
