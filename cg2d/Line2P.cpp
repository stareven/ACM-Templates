#include "Line2P.h"
#include <assert.h>
#include "utils.h"
#include "Vector.h"
#include "Line.h"

namespace cg2d {

Line2P::Line2P()
{
}

Line2P::Line2P(const Point &_p1, const Point &_p2)
    : p1(_p1), p2(_p2)
{
}


Line2P& Line2P::operator+=(const Vector &v)
{
    p1 += v;
    p2 += v;
    return *this;
}

Line2P& Line2P::operator-=(const Vector &v)
{
    p1 -= v;
    p2 -= v;
    return *this;
}


Line2P operator+(const Line2P &l, const Vector &v)
{
    return Line2P(l) += v;
}

Line2P operator-(const Line2P &l, const Vector &v)
{
    return Line2P(l) -= v;
}


bool parallel(const Line2P &l1, const Line2P &l2)
{
    return eq0((l1.p2 - l1.p1) ^ (l2.p2 - l2.p1));
}

bool collinear(const Line2P &l1, const Line2P &l2)
{
    if (!parallel(l1, l2)) return false;
    return eq0((l1.p2 - l1.p1) ^ (l2.p1 - l1.p1));
}

bool intersecting(const Line2P &l1, const Line2P &l2)
{
    return !parallel(l1, l2);
}

Point intersection(const Line2P &l1, const Line2P &l2)
{
    assert(intersecting(l1, l2));
    return intersection(Line(l1.p1, l1.p2), Line(l2.p1, l2.p2));
}


bool on(const Line2P &l, const Point &p)
{
    return collinear(l.p2 - l.p1, p - l.p1);
}

bool counterclockwise(const Line2P &l, const Point &p)
{
    return counterclockwise(l.p2 - l.p1, p - l.p1);
}

bool clockwise(const Line2P &l, const Point &p)
{
    return clockwise(l.p2 - l.p1, p - l.p1);
}

}
