#include "main.h"

ExampleProgram::ExampleProgram()
        : fpsCounter(), points(), colour(0.0f, 0.0f, 0.0f, 1.0f),
          shader(0), transform(1) {
}

void ExampleProgram::init() {    
    std::vector<glm::vec3> values(read("example.data"));

    Nova::Program::init();

    for (auto& val : values) {
        points.push_back(val[0], val[1], val[2], colour);
    }

    transform[3][0] = -0.5;
    shader = std::make_shared<Nova::Shader>(Nova::Shader::stdVertex, Nova::Shader::stdFragment); 
    shader->activate();
}

void ExampleProgram::main_loop() {
    fpsCounter.update_fps();
    shader->set_transform(transform);
    points.draw();
}

void ExampleProgram::finish() {
}
