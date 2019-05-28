#include "main.h"

#ifndef FLYOBJ3_H
#define FLYOBJ3_H

class Flyobj3 {
public:
    Flyobj3() {}
    Flyobj3(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    bool alive;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void lefttick();
    void righttick();
    void costick();
    bounding_box_t getboundingbox();
    double speed;
private:
    VAO *object;
    VAO *object2;    
};

#endif // FLYOBJ3_H
