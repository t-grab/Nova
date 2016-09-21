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
        : m_handle(0), m_width{width}, m_height{height}, m_title{title},
          m_running(), m_finished(), m_program{prg}
{ }

Window::~Window() {
    windows_mutex.lock();
    if (windows.size() == 1U)
        Nova::terminate();
    windows_mutex.unlock();    
} 

void Window::set_title(const std::string& title) {
    m_title = title;
    glfwSetWindowTitle(m_handle, title.c_str());
}

void Window::open() {
    if (!init() || m_handle != nullptr)
        return;
        
    (boost::thread{Window::main, std::ref(*this)}).detach();    
}

void Window::close() {
    glfwSetWindowShouldClose(m_handle, GL_TRUE);
}

void Window::screenshot(const std::string& file_name) const {
    
}

void Window::handle_keys() {
    if (GLFW_PRESS == glfwGetKey(m_handle, GLFW_KEY_ESCAPE))
        close();
}

void Window::wait() {
    std::unique_lock<std::mutex> running_lock(m_running);
    m_finished.wait(running_lock);
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
        return window->m_handle == handle;
    });

    return *(window_iter->get());
}

void Window::glfw_window_size_callback(GLFWwindow* handle, int width, int height) {
    Window& window = get_window(handle); 
    window.m_width = width;
    window.m_height = height;
    window.m_program->on_resize(width, height);
}

void Window::main(Window& window) {   
    window.m_handle = glfwCreateWindow(window.m_width, window.m_height, window.m_title.c_str(), NULL, NULL);
    if (!window.m_handle) {        
        glfwTerminate();
        error << "Window::open(): Could not open window with GLFW!" << Error::Throw;
    }
    
    std::unique_lock<std::mutex> running_lock(window.m_running);

    glfwMakeContextCurrent(window.m_handle);
    glewExperimental = GL_TRUE;
    glewInit();

    glfwSetWindowSizeCallback(window.m_handle, Window::glfw_window_size_callback);

    window.m_program->init();
    while (!glfwWindowShouldClose(window.m_handle)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, window.m_width, window.m_height);

        window.m_program->main_loop();

        glfwSwapBuffers(window.m_handle);
        glfwPollEvents();
    }    
    window.m_program->finish();

    glfwDestroyWindow(window.m_handle);
    window.m_handle = 0;

    running_lock.unlock();
    window.m_finished.notify_all();
}

////////////////////////////////////////////////////////////////////////////////
////////// WINDOW2 IMPLEMENTATION //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::vector<std::unique_ptr<Window2>> Window2::windows;
std::mutex Window2::static_mutex;

Window2::Window2(int width, int height)
        : m_window{nullptr}, m_width{width}, m_height{height} {
    if (!Nova::init())
        throw std::runtime_error("Nova::Window::Window(): Could not initialize Nova");
}

Window2::~Window2() {
    Window2::static_mutex.lock();
    if (Window2::windows.size() < 2U)
        Nova::terminate();
    Window2::static_mutex.unlock();
}

void Window2::init_context() {
    if (m_window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Nova::Window::init_context(): Could not create window");
    }

    glfwMakeContextCurrent(m_window);
    glewExperimental = GL_TRUE;
    glewInit();

    glfwSetWindowSizeCallback(m_window, Window2::resize_callback);
}

void Window2::resize_callback(GLFWwindow* window, int width, int height) {
    auto window_iter = std::find_if(Window2::windows.begin(), Window2::windows.end(),
        [&](const std::unique_ptr<Window2>& nova) {
            return nova->m_window == window;
        }
    );

    (*window_iter)->m_width = width;
    (*window_iter)->m_height = height;
}

int Window2::get_width() const {
    return m_width;
}

int Window2::get_height() const {
    return m_height;
}

void Window2::set_title(const std::string& title) {
    if (m_window != nullptr)
        glfwSetWindowTitle(m_window, title.c_str());
}

bool Window2::is_open() const {
    return glfwWindowShouldClose(m_window);
}

void Window2::open(const std::string& title) {
    m_window = glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, nullptr);
    init_context();
}

void Window2::open(const std::string& title, Window2& context) {
    if (context.m_window != nullptr) {
        m_window = glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, context.m_window);
        init_context();
    } else {
        open(title);
    }
}

void Window2::close() {
    if (m_window != nullptr)
        glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void Window2::destroy() {
    if (m_window != nullptr) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

void Window2::screenshot(const std::string& file_name) {

}

void Window2::swap_buffers() {
    glfwSwapBuffers(m_window);
}

Window2& Window2::create(int width, int height) {
    std::unique_ptr<Window2> new_window{std::move(new Window2(width, height))};

    static_mutex.lock();
    Window2::windows.push_back(std::move(new_window));
    std::unique_ptr<Window2>& win_ptr{Window2::windows.back()};
    Window2& win_ref = *(win_ptr.get());
    static_mutex.unlock();

    return win_ref;
}