#ifndef NOVA_SHADER_H
#define NOVA_SHADER_H

#include "std.h"

class Shader {
    GLuint handle;
    GLint input_colour;

    GLuint compileShader(const std::string& src, GLuint type);

public:
    static const char* stdVertex;
    static const char* stdFragment;

    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    GLuint id() const;
    GLint colour() const;
};

#endif