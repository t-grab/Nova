#include <iostream>
using std::cout;
using std::endl;
#include <stdexcept>

#include "../include/nova.h"

int main() {
    std::cout << "Nova - Tester" << std::endl;

    Nova::Window window{"Window 1", 640, 480};

    try {
        window.open();
    }
    catch (std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
        return 2;
    }
    catch (...) {
        std::cout << "Unknown error!" << std::endl;
        return 1;
    }
    std::cout << "End of Tester" << std::endl;

    while(!window.closing())
        glfwPollEvents();

    window.getThread()->join();

    std::cout << "Ending main now" << std::endl;

    return 0;
}
