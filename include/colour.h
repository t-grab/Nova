#ifndef NOVA_COLOUR_H
#define NOVA_COLOUR_H

#include "std.h"

namespace Nova {
    class Colour {
        GLfloat m_colour[4];        
    public:
        Colour(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        ~Colour();

        GLfloat r() const;
        GLfloat g() const;
        GLfloat b() const;
        GLfloat a() const; 

        bool operator==(const Colour& col) const;
    };
}

#endif