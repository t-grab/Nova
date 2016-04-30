#include "../include/window.h"
using namespace Nova;
using namespace std;

bool initDependencies() {
    static bool initialized{false};
    
    if (!initialized) {
        if (!glfwInit()) {
            cerr << "Error: Could not start GLFW!" << endl;
            return false;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        initialized = true;    
    }
    
    return initialized;    
}

Window::Window(int width, int height) : width{width}, height{height} {}

Window::~Window() {
    
} 

void Window::open() {
    
}

void Window::close() {
    
}