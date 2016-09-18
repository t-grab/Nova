#include "../include/nova.h"

static void glfwErrorCallback(int error, const char* description) {
    glLog << "GLFW Error: code " << error << ", msg: " << description << "\n"
          << Log::Commit; 
}

bool Nova::init() {
    static bool initialized = false;

    if (!initialized) {
        glLog << "Starting GLFW\n" << glfwGetVersionString() << "\n" << Log::Commit;
        glfwSetErrorCallback(glfwErrorCallback);

        if (!glfwInit()) {
            glLog << "Could not start GLFW\n" << Log::Commit; 
            return initialized;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        initialized = true;
    }

    return initialized;
}

void Nova::terminate() {
    if (Nova::init())
        glfwTerminate();
}
