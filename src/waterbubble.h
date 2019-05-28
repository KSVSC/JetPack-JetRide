#include "main.h"

#ifndef WATERBUBBLE_H
#define WATERBUBBLE_H

class Waterbubble {
public:
    Waterbubble() {}
    Waterbubble(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    bool alive;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    double xspeed;
    double yspeed;
    double gravity;
    void lefttick();
    void righttick();
    bounding_box_t getboundingbox();
    bool up;
private:
    VAO *object;
};

#endif // WATERBUBBLE_H
