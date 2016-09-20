#include "../include/window.h"
#include "../include/nova.h"
using namespace Nova;

////////////////////////////////////////////////////////////////////////////////
////////// WINDOW IMPLEMENTATION ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::mutex Window::windows_mutex;
std::vector<std::unique_ptr<Window>> Window::windows;

Window::Window(const std::string& title, int width, int height,
               std::shared_ptr<Program> prg)
        : handle(0), width{width}, height{height}, title{title},
          running(), finished(), program{prg}
{ }

Window::~Window() {
    windows_mutex.lock();
    if (windows.size() == 1U)
        Nova::terminate();
    windows_mutex.unlock();    
} 

void Window::open() {
    if (!init() || handle != nullptr)
        return;
        
    (boost::thread{Window::main, std::ref(*this)}).detach();    
}

void Window::close() {
    glfwSetWindowShouldClose(handle, GL_TRUE);
}

void Window::screenshot(const std::string& file_name) const {
    
}

void Window::handle_keys() {
    if (GLFW_PRESS == glfwGetKey(handle, GLFW_KEY_ESCAPE))
        close();
}

void Window::update_fps_counter() {
    double current_seconds;
    double elapsed_seconds;

    current_seconds = glfwGetTime();
    elapsed_seconds = current_seconds - frame_counter.previous_seconds;

    if (elapsed_seconds > 0.25) {
        frame_counter.previous_seconds = current_seconds;
        double fps = frame_counter.frame_count / static_cast<double>(elapsed_seconds);
        std::stringstream stream;
        stream << title << ", OpenGL @ fps: " << std::fixed << std::setprecision(2) << fps;
        glfwSetWindowTitle(handle, stream.str().c_str());
        frame_counter.frame_count = 0;
    }

    frame_counter.frame_count++;
}

void Window::wait() {
    std::unique_lock<std::mutex> running_lock(running);
    finished.wait(running_lock);
}

////////////////////////////////////////////////////////////////////////////////
////////// WINDOW IMPLEMENTATION - STATIC METHODS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Window& Window::create(const std::string& title, int width, int height,
                       std::shared_ptr<Program> prg) {
    std::unique_ptr<Window> new_window(std::move(new Window(title, width, height, prg)));
    
    windows_mutex.lock();
    windows.push_back(std::move(new_window));
    std::unique_ptr<Window>& window_ptr = windows.at(windows.size() - 1);
    Window& window_ref = *(window_ptr.get());
    windows_mutex.unlock();    

    return window_ref;
}

Window& Window::get_window(GLFWwindow* handle) {
    auto window_iter = std::find_if(windows.begin(), windows.end(),
    [handle](const std::unique_ptr<Window>& window) {
        return window->handle == handle;
    });

    return *(window_iter->get());
}

void Window::glfw_window_size_callback(GLFWwindow* handle, int width, int height) {
    Window& window = get_window(handle); 
    window.width = width;
    window.height = height;
    window.program->on_resize(width, height);
}

void Window::main(Window& window) {   
    window.handle = glfwCreateWindow(window.width, window.height, window.title.c_str(), NULL, NULL);
    if (!window.handle) {        
        glfwTerminate();
        error << "Window::open(): Could not open window with GLFW!" << Error::Throw;
    }
    
    std::unique_lock<std::mutex> running_lock(window.running);

    glfwMakeContextCurrent(window.handle);
    glewExperimental = GL_TRUE;
    glewInit();

    glfwSetWindowSizeCallback(window.handle, Window::glfw_window_size_callback);

    window.program->init();
    while (!glfwWindowShouldClose(window.handle)) {
        window.update_fps_counter();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, window.width, window.height);

        window.program->main();

        glfwSwapBuffers(window.handle);
        glfwPollEvents();
        window.handle_keys();
    }    
    window.program->finish();

    glfwDestroyWindow(window.handle);
    window.handle = 0;

    running_lock.unlock();
    window.finished.notify_all();
}