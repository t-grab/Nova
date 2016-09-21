#include "../include/shader.h"
using namespace Nova;
/*
const char* Shader::stdVertex = "#version 410\n"
                                "layout(location = 0) in vec3 vertex_position;"
                                "layout(location = 1) in vec4 vertex_colour;"
                                "uniform mat4 model;"
                                "out vec4 colour;"
                                "void main() {"
                                "   colour = vertex_colour;"
                                "   gl_Position = model * vec4(vertex_position, 1.0);"
                                "}";
const char* Shader::stdFragment = "#version 410\n"
                                  "in vec4 colour;"
                                  "out vec4 frag_colour;"
                                  "void main() {"
                                  "    frag_colour = colour;"
                                  "}"; 

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
    : handle(0), matrix(0)
{
    GLuint vertex = compile_shader(vertexSrc, GL_VERTEX_SHADER);
    GLuint fragment = compile_shader(fragmentSrc, GL_FRAGMENT_SHADER);
    
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

    matrix = glGetUniformLocation(handle, "matrix");
}

GLuint Shader::compile_shader(const std::string& src, GLuint type) {
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

void Shader::set_transform(const glm::mat4& mat) {
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mat[0][0]);
}
*/
////////////////////////////////////////////////////////////////////////////////
////////// SHADER //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Shader::Shader(uint_t shader, uint64_t id)
        : m_shader{shader}, m_id{id} {
}

Shader::~Shader() {
}

int_t Shader::get_uniform(const std::string& name) const {
    return glGetUniformLocation(m_shader, name.c_str());
}

////////////////////////////////////////////////////////////////////////////////
////////// VERTEX SHADER ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::mutex VertexShader::static_mutex;
std::vector<std::shared_ptr<VertexShader>> VertexShader::shaders;
std::string VertexShader::standard = "#version 410\n"
                                     "layout(location = 0) in vec3 vertex_position;"
                                     "layout(location = 1) in vec4 vertex_colour;"
                                     "uniform mat4 model;"
                                     "out vec4 colour;"
                                     "void main() {"
                                     "   colour = vertex_colour;"
                                     "   gl_Position = model * vec4(vertex_position, 1.0);"
                                     "}";

VertexShader::VertexShader(uint_t shader, uint64_t id)
        : Shader(shader, id) {
}

std::shared_ptr<VertexShader> VertexShader::compile(const std::string& src) {
    VertexShader::static_mutex.lock();
    auto shader = Shader::compile<VertexShader>(src, GL_VERTEX_SHADER,
                                                VertexShader::shaders);
    VertexShader::static_mutex.unlock();
    return shader;
}

////////////////////////////////////////////////////////////////////////////////
////////// FRAGMENT SHADER /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::mutex FragmentShader::static_mutex;
std::vector<std::shared_ptr<FragmentShader>> FragmentShader::shaders;
std::string FragmentShader::standard = "#version 410\n"
                                       "in vec4 colour;"
                                       "out vec4 frag_colour;"
                                       "void main() {"
                                       "    frag_colour = colour;"
                                       "}";

FragmentShader::FragmentShader(uint_t shader, uint64_t id)
        : Shader(shader, id) {
}

std::shared_ptr<FragmentShader> FragmentShader::compile(const std::string& src) {
    FragmentShader::static_mutex.lock();
    auto shader = Shader::compile<FragmentShader>(src, GL_FRAGMENT_SHADER,
                                                  FragmentShader::shaders);
    FragmentShader::static_mutex.unlock();    
    return shader;    
}

////////////////////////////////////////////////////////////////////////////////
////////// SHADER PROGRAM //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::mutex ShaderProgram::static_mutex;
std::vector<std::shared_ptr<ShaderProgram>> ShaderProgram::shaders;

ShaderProgram::ShaderProgram(uint_t program, uint64_t id)
        : m_program{program}, m_id{id} {
}

ShaderProgram::~ShaderProgram() {
}

std::shared_ptr<ShaderProgram> ShaderProgram::link(std::shared_ptr<VertexShader> vertex,
                                                   std::shared_ptr<FragmentShader> fragment) {
    uint_t program = glCreateProgram();
    glAttachShader(program, vertex->m_shader);
    glAttachShader(program, fragment->m_shader);
    glLinkProgram(program);

    int params = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    if (params != GL_TRUE) {
        const int max_length = 2048;
        int actual_length = 0;
        char log[max_length];

        glGetProgramInfoLog(program, max_length, &actual_length, log);
        error << "Error: Shader program " << program << " did not link!\n"
              << "Linker Output: \n"
              << log << "\n"
              << Error::Throw;
    }

    ShaderProgram::static_mutex.lock();
    uint64_t size{ShaderProgram::shaders.size()};
    std::shared_ptr<ShaderProgram> program_ptr{new ShaderProgram(program, size)};
    ShaderProgram::shaders.push_back(program_ptr);
    ShaderProgram::static_mutex.unlock();

    return program_ptr;
}
