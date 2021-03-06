#include <iostream>
using std::cout;
using std::endl;
#include <stdexcept>

#include "../include/nova.h"
#include "main.h"

const std::string TITLE = "Nova example Application";
const std::string END = "Closing Nova example application";

class TestProg : public Nova::Program2 {
    std::vector<glm::vec3> data;
public:
    TestProg() : Nova::Program2("Nova::Program2"), data(read("example.data")) { }

    void loop() {

    }
};

int main() {
    try {
        std::cout << TITLE << std::endl;

        auto program = Nova::Program2::run<TestProg>();
        program->join();

/*      auto program = std::make_shared<ExampleProgram>();
        Nova::Window& window = Nova::Window::create("Window 1", 640, 480, program);

        window.open();
        window.wait();
*/
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
