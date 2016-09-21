#ifndef NOVA_H
#define NOVA_H

#include "std.h"
#include "shader.h"
#include "window.h"
#include "program.h"
#include "points.h"
#include "fpsCounter.h"
#include "context.h"

namespace Nova {
    bool init();
    void terminate();
    void log_params();
}

#endif