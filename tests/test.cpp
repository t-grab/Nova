#include <iostream>
using std::cout;
using std::endl;
#include <stdexcept>

#include "../include/nova.h"

const std::string TITLE = "Nova example Application";
const std::string END = "Closing Nova example application";

class ExampleProgram : public Nova::Program {
    Nova::Points points;
    Nova::Colour colour;
public:
    ExampleProgram() : points(), colour(0.0f, 0.0f, 0.0f, 1.0f) {}

    void init() {
        Nova::Program::init();

        points.push_back(0.25f,  0.25f, colour);
        points.push_back(0.5f,  0.5f, colour);
        points.push_back(0.5f, -0.5f, colour);

        Shader shader(Shader::stdVertex, Shader::stdFragment);
        shader.activate();
    }

    void main() {
        points.draw();
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
