#include "../include/shader.h"

const char* Shader::stdVertex = "#version 410\n"
                                "layout(location = 0) in vec3 vertex_position;"
                                "layout(location = 1) in vec4 vertex_colour;"
                                "out vec4 colour;"
                                "void main() {"
                                "   colour = vertex_colour;"
                                "   gl_Position = vec4(vertex_position, 1.0);"
                                "}";
const char* Shader::stdFragment = "#version 410\n"
                                  "in vec4 colour;"
                                  "out vec4 frag_colour;"
                                  "void main() {"
                                  "    frag_colour = colour;"
                                  "}"; 

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
    : handle(0)
{
    GLuint vertex = compileShader(vertexSrc, GL_VERTEX_SHADER);
    GLuint fragment = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);
    
    handle = glCreateProgram();
    glAttachShader(handle, fragment);
    glAttachShader(handle, vertex);
    glLinkProgram(handle);

    int params = -1;
    glGetProgramiv(handle, GL_LINK_STATUS, &params);
    if (params != GL_TRUE) {
        const int max_length = 2048;
        int actual_length = 0;
        char log[max_length];

        glGetProgramInfoLog(handle, max_length, &actual_length, log);
        error << "Error: Shader program " << handle << " did not link!\n"
              << "Linker Output: \n"
              << log << "\n"
              << Error::Throw;
    }
}

GLuint Shader::compileShader(const std::string& src, GLuint type) {
    auto cstr = src.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);
    
    int params = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        const int max_length = 2048;
        int actual_length = 0;
        char log[max_length];

        glGetShaderInfoLog(shader, max_length, &actual_length, log);
        error << "Error: Shader " << shader << " did not compile!\n"
              << "Compiler Output: \n"
              << log << "\n"
              << Error::Throw;
    }

    return shader;
}

void Shader::activate() const {
    glUseProgram(handle);
}