#include "timer.h"
#include <GLFW/glfw3.h>

Timer::Timer(double interval) {
    prev = glfwGetTime();
    this->interval = interval;
}

bool Timer::processTick() {
    double cur = glfwGetTime();
    if (cur - prev >= interval) {
        prev = cur;
        return true;
    } else
        return false;
}
