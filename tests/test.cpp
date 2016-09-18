#include <iostream>
using std::cout;
using std::endl;
#include <stdexcept>

#include "../include/nova.h"

const std::string TITLE = "Nova example Application";
const std::string END = "Closing Nova example application";

int main() {
    try {
        std::cout << TITLE << std::endl;

        Nova::Window& window = Nova::Window::create("Window 1", 640, 480);
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
