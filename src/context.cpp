#include "../include/context.h"
using namespace Nova;

void OpenGLContext::clear(bitfield_t bits) {
    glClear(bits);
}

void OpenGLContext::viewport(int_t x, int_t y, int width, int height) {
    glViewport(x, y, width, height);
}