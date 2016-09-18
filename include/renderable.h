#ifndef NOVA_RENDERABLE_H
#define NOVA_RENDERABLE_H

#include "std.h"

struct Renderable {
    virtual void render() = 0;
};

#endif