#include "Line.h"
#include <assert.h>
#include "utils.h"
#include "Point.h"

namespace cg2d {

Line::Line()
    : a(0), b(0), c(0)
{
}

Line::Line(double _a, double _b, double _c)
    : a(_a), b(_b), c(_c)
{
}

Line::Line(const Point &p1, const Point &p2)
{
    // (y - y1) / (x - x1) > (y2 - y1) / (x2 - x1)
    // (y2 - y1)x - (x2 - x1)y - (y2 - y1)x1 + (x2 - x1)y1 < 0
    // ---------  -----------  ---------------------------
    // a          b          c
    a = (p2.y - p1.y);
    b = -(p2.x - p1.x);
    c = -(p2.y - p1.y) * p1.x + (p2.x - p1.x) * p1.y;
}


double Line::substitude(const Point &p) const
{
    return a * p.x + b * p.y + c;
}

double Line::distance(const Point &p) const
{
    return fabs(substitude(p)) / sqrtl(a * a + b * b);
}


bool parallel(const Line &l1, const Line &l2)
{
    return eq0(l1.a * l2.b - l2.a * l1.b);
}

bool collinear(const Line &l1, const Line &l2)
{
    if (!parallel(l1, l2)) return false;
    return eq0(l1.a * l2.c - l2.a * l1.c);
}

bool intersecting(const Line &l1, const Line &l2)
{
    return !parallel(l1, l2);
}

Point intersection(const Line &l1, const Line &l2)
{
    // a1 x + b1 y + c1 = 0
    // a2 x + b2 y + c2 = 0

    // x:
    // a1 b2 x + b1 b2 y + b2 c1 = 0
    // a2 b1 x + b1 b2 y + b1 c2 = 0
    // =>
    // x = - (b2 c1 - b1 c2) / (a1 b2 - a2 b1)

    // y:
    // a1 a2 x + a2 b1 y + a2 c1 = 0
    // a1 a2 x + a1 b2 y + a1 c2 = 0
    // =>
    // y = (a2 c1 - a1 c2) / (a1 b2 - a2 b1)
    double d = l1.a * l2.b - l2.a * l1.b;
    assert(!eq0(d));
    double x = l2.b * l1.c - l1.b * l2.c;
    double y = l2.a * l1.c - l1.a * l2.c;
    return Point(-x / d, y / d);
}


bool on(const Line &l, const Point &p)
{
    return eq0(l.substitude(p));
}

bool counterclockwise(const Line &l, const Point &p)
{
    return lt0(l.substitude(p));
}

bool clockwise(const Line &l, const Point &p)
{
    return gt0(l.substitude(p));
}

}
