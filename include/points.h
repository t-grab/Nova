
#ifndef NOVA_POINTS_H
#define NOVA_POINTS_H

#include "std.h"
#include "renderable.h"

template<uint N = 3>
class Point {
    GLfloat m_pos[N];
    GLfloat m_col[4];
public:
    Point();
};

template<uint N = 3>
class Points : public Renderable {
    std::vector<Point> m_points;
public:
    Points();
    ~Points();

    virtual void render();
};

#endif
