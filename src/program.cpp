#include "../include/program.h"
#include "../include/nova.h"

void Nova::Program::init() {
    Nova::log_params();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}