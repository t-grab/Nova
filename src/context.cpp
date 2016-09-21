#include "../include/context.h"
using namespace Nova;

void OpenGLContext::clear_color(float_t r, float_t g, float_t b, float_t a) {
    glClearColor(r, g, b, a);
}

void OpenGLContext::clear(bitfield_t bits) {
    glClear(bits);
}

void OpenGLContext::viewport(int_t x, int_t y, int width, int height) {
    glViewport(x, y, width, height);
}

void OpenGLContext::set_uniform_matrix(int_t location, int count, bool transpose,
                                       glm::mat4 value) {
    auto gl_transpose = transpose ? GL_TRUE : GL_FALSE;
    glUniformMatrix4fv(location, count, gl_transpose, &value[0][0]);
}