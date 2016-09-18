#include <iostream>
using std::cout;
using std::endl;
#include <stdexcept>

#include "../include/nova.h"

const std::string TITLE = "Nova example Application";
const std::string END = "Closing Nova example application";

class ExampleProgram : public Nova::Program {
    GLuint m_vao;
public:
    void init() {
        Nova::Program::init();

        GLfloat points[] = {
             0.0f,  0.5f,  0.0f,
             0.5f, -0.5f,  0.0f,
            -0.5f, -0.5f,  0.0f, 
        };

        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        m_vao = 0;
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        Shader shader(Shader::stdVertex, Shader::stdFragment);
        glUseProgram(shader.id());
        glUniform4f(shader.colour(), 0.0f, 0.0f, 0.0f, 1.0f);
    }

    void main() {
        glBindVertexArray(m_vao);
        glDrawArrays(GL_POINTS, 0, 3);
    }

    void finish() {
    }
};

int main() {
    try {
        std::cout << TITLE << std::endl;

        auto program = std::make_shared<ExampleProgram>();
        Nova::Window& window = Nova::Window::create("Window 1", 640, 480, program);

        window.open();
        while(!window.closing())
            glfwPollEvents();
        Nova::join(window);

        std::cout << END << std::endl;
        return 0;
    }
    catch (std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
        return 2;
    }
    catch (...) {
        std::cout << "Unknown error!" << std::endl;
        return 1;
    }
}
