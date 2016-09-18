#include "../include/window.h"
using namespace Nova;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
////////// SUPPORT FUNCTIONS AND VARIABLES /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Nova::join(Nova::Window& window) {
    window.getThread()->join();
}

void Nova::join(std::vector<std::reference_wrapper<Nova::Window>> windows) {
    for (auto& window : windows)
        Nova::join(window);
}

////////////////////////////////////////////////////////////////////////////////
////////// WINDOW IMPLEMENTATION ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::mutex Window::windows_mutex;
std::vector<std::unique_ptr<Window>> Window::windows;

Window::Window(const string& title, int width, int height)
    : handle(0), width{width}, height{height}, title{title}, thread{0}
{ }

Window::~Window() {
    windows_mutex.lock();
    if (windows.size() == 1U)
        Nova::terminate();
    windows_mutex.unlock();    
} 

boost::thread* Window::getThread() {
    return thread;
}

bool Window::closing() {
    return glfwWindowShouldClose(handle);
}

void Window::open() {
    if (!init())
        return;
        
    handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!handle) {        
        glfwTerminate();
        error << "Window::open(): Could not open window with GLFW!" << Error::Throw;
    }    

    thread = new boost::thread{Window::main, std::ref(*this)};    
}

void Window::close() {
    glfwSetWindowShouldClose(handle, GL_TRUE);
}

void Window::handle_keys() {
    if (GLFW_PRESS == glfwGetKey(handle, GLFW_KEY_ESCAPE))
        close();
}

Window& Window::create(const string& title, int width, int height) {
    unique_ptr<Window> new_window(std::move(new Window(title, width, height)));
    
    windows_mutex.lock();
    windows.push_back(std::move(new_window));
    unique_ptr<Window>& window_ptr = windows.at(windows.size() - 1);
    Window& window_ref = *(window_ptr.get());
    windows_mutex.unlock();    

    return window_ref;
}

Window& Window::get_window(GLFWwindow* handle) {
    auto window_iter = std::find_if(windows.begin(), windows.end(),
    [handle](const unique_ptr<Window>& window) {
        return window->handle == handle;
    });

    return *(window_iter->get());
}

void Window::glfw_window_size_callback(GLFWwindow* handle, int width, int height) {
    Window& window = get_window(handle); 
    window.width = width;
    window.height = height;
}

void Window::main(Window& window) {
    glfwMakeContextCurrent(window.handle);
    glewExperimental = GL_TRUE;
    glewInit();

    glfwSetWindowSizeCallback(window.handle, Window::glfw_window_size_callback);

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
        window.handle_keys();        

        glfwSwapBuffers(window.handle);        
    }
}