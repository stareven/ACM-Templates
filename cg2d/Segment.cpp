#include "Segment.h"
#include <algorithm>
#include "utils.h"
#include "Vector.h"
#include "Line2P.h"
#include "Line.h"

namespace cg2d {

using namespace std;

Segment::Segment()
{
}

Segment::Segment(const Point &p1_, const Point &p2_)
    : p1(p1_), p2(p2_)
{
}


double Segment::length() const
{
    return (p2 - p1).length();
}


Segment& Segment::operator+=(const Vector &v)
{
    p1 += v;
    p2 += v;
    return *this;
}

Segment& Segment::operator-=(const Vector &v)
{
    p1 -= v;
    p2 -= v;
    return *this;
}


Segment operator+(const Segment &s, const Vector &v)
{
    return Segment(s) += v;
}

Segment operator-(const Segment &s, const Vector &v)
{
    return Segment(s) -= v;
}


bool intersecting(const Line2P &l, const Segment &s)
{
    Vector v_line = l.p2 - l.p1;
    Vector v_p1 = s.p1 - l.p1;
    Vector v_p2 = s.p2 - l.p1;
    return le0((v_line ^ v_p1) * (v_line ^ v_p2));
}

bool strict_intersecting(const Line2P &l, const Segment &s)
{
    Vector v_line = l.p2 - l.p1;
    Vector v_p1 = s.p1 - l.p1;
    Vector v_p2 = s.p2 - l.p1;
    return lt0((v_line ^ v_p1) * (v_line ^ v_p2));
}

bool intersecting(const Line &l, const Segment &s)
{
    return le0(l.substitude(s.p1) * l.substitude(s.p2));
}

bool strict_intersecting(const Line &l, const Segment &s)
{
    return lt0(l.substitude(s.p1) * l.substitude(s.p2));
}

bool intersecting(const Segment &s1, const Segment &s2)
{
    // fast box check
    Point s1p1(min(s1.p1.x, s1.p2.x), min(s1.p1.y, s1.p2.y));
    Point s1p2(max(s1.p1.x, s1.p2.x), max(s1.p1.y, s1.p2.y));
    Point s2p1(min(s2.p1.x, s2.p2.x), min(s2.p1.y, s2.p2.y));
    Point s2p2(max(s2.p1.x, s2.p2.x), max(s2.p1.y, s2.p2.y));
    if (s2p1.x > s1p2.x) return false;
    if (s2p1.y > s1p2.y) return false;
    if (s2p2.x < s1p1.x) return false;
    if (s2p2.y < s1p1.y) return false;
    // check
    return intersecting(Line2P(s1.p1, s1.p2), s2) &&
        intersecting(Line2P(s2.p1, s2.p2), s1);
}

}
