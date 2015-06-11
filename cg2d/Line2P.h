#ifndef _CG2D_LINE2P_H_
#define _CG2D_LINE2P_H_

#include "Point.h"

namespace cg2d {

class Vector;

class Line2P
{
public:
    explicit Line2P();
    explicit Line2P(const Point &_p1, const Point &_p2);

public:
    Line2P& operator+=(const Vector &v);
    Line2P& operator-=(const Vector &v);

public:
    Point p1, p2;

};

Line2P operator+(const Line2P &l, const Vector &v);
Line2P operator-(const Line2P &l, const Vector &v);

bool parallel(const Line2P &l1, const Line2P &l2);
bool collinear(const Line2P &l1, const Line2P &l2);
bool intersecting(const Line2P &l1, const Line2P &l2);
Point intersection(const Line2P &l1, const Line2P &l2);

bool on(const Line2P &l, const Point &p);
bool counterclockwise(const Line2P &l, const Point &p);
bool clockwise(const Line2P &l, const Point &p);

}

#endif // _CG2D_LINE2P_H_
