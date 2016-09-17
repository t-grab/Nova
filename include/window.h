#ifndef NOVA_WINDOW_H
#define NOVA_WINDOW_H

#include "std.h"
#include "shader.h"
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
        
        static void main(Window& window); 
        
    public:
        Window(const string& title, int width, int height);
        ~Window();
        
        boost::thread* getThread();
                
        bool closing();

        void open();
        void close();        
    };
}

#endif