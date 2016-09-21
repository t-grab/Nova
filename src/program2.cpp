#include "../include/program2.h"
using namespace Nova;

Program2::Program2(const std::string& title, int width, int height)
        : m_window{Window2::create(width, height)}, m_context(), m_title{title},
          m_thread() {
}

Program2::~Program2() {
}

Window2& Program2::window() {
    return m_window;
}

OpenGLContext& Program2::context() {
    return m_context;
}

const std::string& Program2::get_title() const {
    return m_title;
}

void Program2::set_title(const std::string& title) {
    m_title = title;
    if (m_window.is_open())
        m_window.set_title(title);
}

void Program2::init() {
    m_window.open(m_title);
    m_context.clear_color(1.0f, 1.0f, 1.0f, 1.0f);
}

void Program2::main() {
    while (m_window.is_open()) {
        m_context.clear(OpenGLContext::Color | OpenGLContext::Depth);
        m_context.viewport(0, 0, m_window.get_width(), m_window.get_height());

        loop();

        glfwPollEvents();
        m_window.swap_buffers();
    }
}

void Program2::loop() {
    
}

void Program2::finish() {
    m_window.destroy();
}

void Program2::join() {
    m_thread.join();
}

void Program2::start_thread(std::shared_ptr<Program2> program) {
    program->init();
    program->main();
    program->finish();
}