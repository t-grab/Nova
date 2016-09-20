#ifndef EXAMPLE_MAIN_H
#define EXAMPLE_MAIN_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "../include/nova.h"

class ExampleProgram : public Nova::Program {
    Nova::Points points;
    Nova::Colour colour;
public:
    ExampleProgram();

    virtual void init();
    virtual void main();
    virtual void finish();    
};

std::vector<glm::vec3> read(const std::string& file_name); 

#endif