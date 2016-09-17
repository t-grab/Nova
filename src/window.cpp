#include "../include/window.h"
using namespace Nova;
using namespace std;

// ------------------- Support functions and variables -------------------//

bool glfwError{false};

static bool initDependencies() {
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
        glfwWindowHint(GLFW_SAMPLES, 4);
                    
        glfwMakeContextCurrent(NULL);
        
        glewExperimental = GL_TRUE;
        glewInit();
        
        initialized = true;    
    }
    
    return initialized;
}

// ------------------- Window implementation ------------------- //

Window::Window(const string& title, int width, int height)
    : width{width}, height{height}, title{title}, thread{0}
{ }

Window::~Window() {
} 

boost::thread* Window::getThread() {
    return thread;
}

bool Window::closing() {
    return glfwWindowShouldClose(handle);
}

void Window::open() {
    if (glfwError || !initDependencies())
        return;
        
    handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!handle) {
        glfwError = true;
        glfwTerminate();
        throw runtime_error("Window::open(): Could not open window with GLFW!");
    }    
    
    thread = new boost::thread{Window::main, *this};    
}

void Window::close() {
    glfwSetWindowShouldClose(handle, GL_TRUE);
}

void Window::main(Window& window) {    
    glfwMakeContextCurrent(window.handle);
    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    GLfloat points[] = {
         0.0f,  0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f, 
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    Shader shader(Shader::stdVertex, Shader::stdFragment);
    glUseProgram(shader.id());

    while (!glfwWindowShouldClose(window.handle)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, window.width, window.height);
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window.handle);        
    }
}