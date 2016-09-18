#ifndef NOVA_WINDOW_H
#define NOVA_WINDOW_H

#include "std.h"
#include "shader.h"
#include <mutex>
#include <boost/thread.hpp>

namespace Nova {
    using namespace Nova;
    using namespace std;
    
    class Window {
        GLFWwindow* handle;
        int width;
        int height;
        string title;
        boost::thread* thread;
        
        Window(const string& title, int width, int height);
        void handle_keys();

        static std::mutex creation_mutex;
        static std::vector<unique_ptr<Window>> windows;
        static Window& get_window(GLFWwindow* handle);
        static void glfw_window_size_callback(GLFWwindow* handle, int width, int height);
        static void main(Window& window); 
        
    public:        
        ~Window();        
        boost::thread* getThread();                
        bool closing();
        void open();
        void close();  

        static Window& create(const string& title, int width, int height);      
    };

    void join(Window& window);
    void join(std::vector<std::reference_wrapper<Window>> windows);
}

#endif