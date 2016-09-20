#ifndef NOVA_RENDERABLE_H
#define NOVA_RENDERABLE_H

#include "std.h"

namespace Nova {
    struct Drawable {
        virtual void draw() = 0;
    };
}

#endif