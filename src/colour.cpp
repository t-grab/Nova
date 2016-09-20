#include "../include/colour.h"
using namespace Nova;

Colour::Colour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
        : m_colour{ r, g, b, a } {        
}

Colour::~Colour() {
}

GLfloat Colour::r() const {
    return m_colour[0];
}

GLfloat Colour::g() const {
    return m_colour[1];
}

GLfloat Colour::b() const {
    return m_colour[2];
}

GLfloat Colour::a() const {
    return m_colour[3];
}

bool Colour::operator==(const Colour& col) const {
    return m_colour[0] == col.m_colour[0] &&
           m_colour[1] == col.m_colour[1] &&
           m_colour[2] == col.m_colour[2] &&
           m_colour[3] == col.m_colour[3];
}
