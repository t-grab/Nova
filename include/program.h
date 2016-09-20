#ifndef NOVA_PROGRAM_H
#define NOVA_PROGRAM_H

#include "std.h"

namespace Nova {
    class Program {
    public:
        virtual void init();
        virtual void main_loop() = 0;
        virtual void finish() = 0;

        virtual void on_resize(int width, int height);
        virtual void on_key();
    };
}

#endif