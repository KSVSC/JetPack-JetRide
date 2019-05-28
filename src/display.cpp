#include "display.h"
#include "main.h"
#include <cstring>

Display::Display()
{
    score = 0;
    digslen = 0;
    position.x = 0;
    position.y = 3.5;
}

void Display::update(int score) {
    this->score = score;
    char scorestr[50];
    sprintf(scorestr, "%d", score);
    digslen = strlen(scorestr);
    for (int i = digslen - 1; i >= 0; i--) {
        digs[i] = Number(scorestr[i], 4 - 0.3*(digslen - i) + position.x, position.y);
    }
}

int Display::view() {
    return score;
}

void Display::reset(){
    score =0;
}

void Display::draw(glm::mat4 VP) {
    for (int i = 0; i < digslen; i++) digs[i].draw(VP);
}

void Display::set_position(float x, float y){
    this->position = glm::vec3(x, y, 0);
}