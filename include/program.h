#ifndef NOVA_PROGRAM_H
#define NOVA_PROGRAM_H

#include "std.h"

namespace Nova {
    class Program {
    public:
        virtual void init();
        virtual void main() = 0;
        virtual void finish() = 0;
    };
}

#endif