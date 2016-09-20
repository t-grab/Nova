#ifndef NOVA_SHADER_H
#define NOVA_SHADER_H

#include "std.h"

namespace Nova {
    class Shader {
        GLuint handle;
        GLint matrix;

        GLuint compile_shader(const std::string& src, GLuint type);

    public:
        static const char* stdVertex;
        static const char* stdFragment;

        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);    
        void activate() const;
        void set_transform(const glm::mat4& mat);
    };
}

#endif