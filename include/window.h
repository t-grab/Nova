#ifndef NOVA_WINDOW_H
#define NOVA_WINDOW_H

#include "std.h"
#include <thread>

namespace Nova {
    class Window {
        GLFWwindow* handle;
        
        int width;
        int height;
        
    public:
        Window(int width, int height);
        ~Window();
        
        void open();
        void close();
    };
}

#endif