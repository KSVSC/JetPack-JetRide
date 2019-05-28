#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player() {}
    Player(float x, float y,float speed, color_t color);
    glm::vec3 position;
    float rotation;
    float offset;
    int score;
    bool shield;
    bool cut;
    bool jump;
    int safe;
    int t;
    int var;
    void update_score(int x);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void lefttick();
    void righttick();
    void uptick();
    void downtick();
    bounding_box_t getboundingbox();
    float speed;
    double acceleration;
    double speed2;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;   
};

#endif // PLAYER_H
