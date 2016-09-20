
#ifndef NOVA_POINTS_H
#define NOVA_POINTS_H

#include "std.h"
#include "drawable.h"
#include "colour.h"

namespace Nova {
    class Points : public Drawable {
        std::vector<GLfloat> m_points;
        std::vector<GLfloat> m_colours;
        GLuint m_vao;

    public:
        Points();
        ~Points();

        void push_back(GLfloat x, GLfloat y, const Colour& col);
        void push_back(GLfloat x, GLfloat y, GLfloat z, const Colour& col);
        virtual void draw();
    };
}

#endif
