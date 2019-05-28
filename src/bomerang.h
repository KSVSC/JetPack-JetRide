#include "main.h"

#ifndef BOMERANG_H
#define BOMERANG_H

class Bomerang {
public:
    Bomerang() {}
    Bomerang(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    bool alive;
    int t;
    float x;
    float y;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void lefttick();
    void righttick();
    void tick();
    bounding_box_t getboundingbox();
    double speed;
private:
    VAO *object;
    VAO *object1;
};

#endif // BOMERANG_H
