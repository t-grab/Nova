#ifndef NOVA_FRAME_COUNTER_H
#define NOVA_FRAME_COUNTER_H

#include "std.h"

namespace Nova {
    class FpsCounter {
        double m_prev;
        int m_count;
        double m_prec;

        double m_fps;

    public:
        FpsCounter(double precision = 0.25);

        void update_fps();
        double fps() const;
    };
}

#endif