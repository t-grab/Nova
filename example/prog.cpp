#include "main.h"

ExampleProgram::ExampleProgram() : points(), colour(0.0f, 0.0f, 0.0f, 1.0f) { }

void ExampleProgram::init() {
    std::vector<glm::vec3> values(read("example.data"));

    Nova::Program::init();

    for (auto& val : values) {
        points.push_back(val[0], val[1], val[2], colour);
    }

    Shader shader(Shader::stdVertex, Shader::stdFragment);
    shader.activate();
}

void ExampleProgram::main() {
    points.draw();
}

void ExampleProgram::finish() {
}
