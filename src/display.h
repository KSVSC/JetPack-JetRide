#ifndef DISPLAY_H
#define DISPLAY_H

#include "number.h"

class Display
{
public:
    Display();
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void update(int score);
    int view();
    void reset();
    void set_position(float a, float b);

private:
    int score, digslen;
    Number digs[50];
};

#endif // DISPLAY_H