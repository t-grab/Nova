#ifndef NOVA_OPEN_GL_CONTEXT_H
#define NOVA_OPEN_GL_CONTEXT_H

#include "std.h"

namespace Nova {
    class OpenGLContext {
    public:
        enum BufferBits {
            Color = GL_COLOR_BUFFER_BIT,
            Depth = GL_DEPTH_BUFFER_BIT,
            Accumulation = GL_ACCUM_BUFFER_BIT,
            Stencil = GL_STENCIL_BUFFER_BIT
        };

        void clear(bitfield_t bits);
        void viewport(int_t x, int_t y, int width, int height);
    };
}

#endif