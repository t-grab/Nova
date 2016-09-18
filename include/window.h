#ifndef NOVA_WINDOW_H
#define NOVA_WINDOW_H

#include "std.h"
#include "program.h"
#include <mutex>
#include <boost/thread.hpp>

namespace Nova {    
    class Window {
        GLFWwindow* handle;
        int width;
        int height;
        std::string title;
        boost::thread* thread;
        std::shared_ptr<Nova::Program> program;

        struct FrameCounter {
            double previous_seconds;
            int frame_count;
        } frame_counter;

        Window(const std::string& title, int width, int height,
               std::shared_ptr<Nova::Program> prg);
        void handle_keys();
        void update_fps_counter();

        static std::mutex windows_mutex;
        static std::vector<std::unique_ptr<Window>> windows;
        static Window& get_window(GLFWwindow* handle);
        static void glfw_window_size_callback(GLFWwindow* handle, int width, int height);
        static void main(Window& window); 
        
    public:        
        ~Window();        
        boost::thread* getThread();                
        bool closing();
        void open();
        void close();  

        static Window& create(const std::string& title, int width, int height,
                              std::shared_ptr<Nova::Program> prg);      
    };

    void join(Window& window);
    void join(std::vector<std::reference_wrapper<Window>> windows);
}

#endif