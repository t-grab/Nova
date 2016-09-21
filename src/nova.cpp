#include "../include/nova.h"
using namespace Nova;

Log Nova::glLog("gl.log");
std::mutex init_mutex;

static void glfwErrorCallback(int error, const char* description) {
    glLog << "GLFW Error: code " << error << ", msg: " << description << "\n"
          << Log::Commit; 
}

bool Nova::init() {
    init_mutex.lock();
    static bool initialized = false;

    if (!initialized) {
        glLog << "Starting GLFW\n" << glfwGetVersionString() << "\n" << Log::Commit;
        glfwSetErrorCallback(glfwErrorCallback);

        if (!glfwInit()) {
            glLog << "Could not start GLFW\n" << Log::Commit;
            init_mutex.unlock(); 
            return initialized;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        initialized = true;
    }

    init_mutex.unlock();
    return initialized;
}

void Nova::terminate() {
    init_mutex.lock();
    if (Nova::init())
        glfwTerminate();
    init_mutex.unlock();
}

void Nova::log_params() {
    static std::vector<GLenum> params = {
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        GL_MAX_DRAW_BUFFERS,
        GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
        GL_MAX_TEXTURE_IMAGE_UNITS,
        GL_MAX_TEXTURE_SIZE,
        GL_MAX_VARYING_FLOATS,
        GL_MAX_VERTEX_ATTRIBS,
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        GL_MAX_VIEWPORT_DIMS,
        GL_STEREO,
    };

    static std::vector<std::string> names = {
        "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
        "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
        "GL_MAX_DRAW_BUFFERS",
        "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
        "GL_MAX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_TEXTURE_SIZE",
        "GL_MAX_VARYING_FLOATS",
        "GL_MAX_VERTEX_ATTRIBS",
        "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        "GL_MAX_VIEWPORT_DIMS",
        "GL_STEREO",
    };

    glLog << "GL Context Params:\n";
    for (int i = 0; i < params.size() - 2; ++i) {
        int v = 0;
        glGetIntegerv(params[i], &v);
        glLog << names[i] << " " << v << "\n";
    }

    int v[] = { 0, 0 };
    glGetIntegerv(params[params.size() - 2], v);
    glLog << names[names.size() - 2] << " " << v[0] << " " << v[1] << "\n";

    unsigned char s = 0;
    glGetBooleanv(params[params.size() - 1], &s);
    glLog << names[names.size() - 1] << " " << static_cast<uint>(s) << "\n"
          <<Log::Commit;    
}