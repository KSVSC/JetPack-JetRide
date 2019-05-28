#ifndef NUMBER_H
#define NUMBER_H

#include "main.h"
#include "stroke.h"


class Number
{
public:
    Number() {}
    Number(char c, float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    Stroke stroke[7];
};

#endif // NUMBER_H