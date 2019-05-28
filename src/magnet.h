#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    bool alive;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void lefttick();
    void righttick();
    bounding_box_t getboundingbox();
    void disappear();
    double speed;
private:
    VAO *object;
};

#endif // MAGNET_H
