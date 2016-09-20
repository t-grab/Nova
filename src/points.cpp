#include "../include/points.h"
using namespace Nova;

Points::Points()
        : m_points(), m_colours(), m_vao(0) {
}

Points::~Points() {
}

void Points::push_back(GLfloat x, GLfloat y, const Colour& col) {
    push_back(x, y, 0.0f, col);
}

void Points::push_back(GLfloat x, GLfloat y, GLfloat z, const Colour& col) {
    m_vao = 0;

    m_points.push_back(x);
    m_points.push_back(y);
    m_points.push_back(z);

    m_colours.push_back(col.r());
    m_colours.push_back(col.g());
    m_colours.push_back(col.b());
    m_colours.push_back(col.a());
}

void Points::draw() {
    if (m_vao == 0) {
        GLuint point_vbo = 0;
        glGenBuffers(1, &point_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_points.size(), &m_points[0], GL_STATIC_DRAW);

        GLuint colour_vbo = 0;
        glGenBuffers(1, &colour_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colour_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_colours.size(), &m_colours[0], GL_STATIC_DRAW);

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, colour_vbo);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }

    glBindVertexArray(m_vao);
    glDrawArrays(GL_POINTS, 0, 3);
}
