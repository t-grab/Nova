#ifndef EXAMPLE_MAIN_H
#define EXAMPLE_MAIN_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "../include/nova.h"
/*
class ExampleProgram : public Nova::Program {
    Nova::FpsCounter fpsCounter;
    Nova::Points points;
    Nova::Colour colour;
    std::shared_ptr<Nova::Shader> shader;
    glm::mat4 transform;
public:
    ExampleProgram();

    virtual void init();
    virtual void main_loop();
    virtual void finish();    
};
*/
std::vector<glm::vec3> read(const std::string& file_name); 

#endif