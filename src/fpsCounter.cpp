#include "../include/fpsCounter.h"
using namespace Nova;

FpsCounter::FpsCounter(double precision)
        : m_prev(0.0), m_count(0), m_prec(precision), m_fps(0.0) {
}

void FpsCounter::update_fps() {
    double current(0.0);
    double elapsed(0.0);

    current = glfwGetTime();
    elapsed = current - m_prev;

    if (elapsed > m_prec) {
        m_prev = current;
        m_fps = m_count / elapsed;
        m_count = 0;
    }

    m_count++;
}

double FpsCounter::fps() const {
    return m_fps;
}