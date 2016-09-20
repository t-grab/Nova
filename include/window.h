#ifndef NOVA_WINDOW_H
#define NOVA_WINDOW_H

#include "std.h"
#include "program.h"
#include <mutex>
#include <boost/thread.hpp>

namespace Nova {    
    class Window {
        GLFWwindow* m_handle;

        int m_width;
        int m_height;
        std::string m_title;

        std::mutex m_running;
        std::condition_variable m_finished;  

        std::shared_ptr<Nova::Program> m_program;

        Window(const std::string& title, int width, int height,
               std::shared_ptr<Nova::Program> prg);
        void handle_keys();

        static std::mutex windows_mutex;
        static std::vector<std::unique_ptr<Window>> windows;

        static Window& get_window(GLFWwindow* handle);
        static void glfw_window_size_callback(GLFWwindow* handle, int width, int height);
        static void main(Window& window); 
        
    public:        
        ~Window();        
        
        void set_title(const std::string& title);
        void open();
        void close();  
        void wait();
        void screenshot(const std::string& file_name) const;

        static Window& create(const std::string& title, int width, int height,
                              std::shared_ptr<Nova::Program> prg);      
    };
}

#endif