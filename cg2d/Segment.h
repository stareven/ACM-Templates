#ifndef _CG2D_SEGMENT_H_
#define _CG2D_SEGMENT_H_

#include "Point.h"

namespace cg2d {

class Vector;
class Line2P;
class Line;

class Segment
{
public:
    explicit Segment();
    explicit Segment(const Point &p1_, const Point &p2_);

public:
    double length() const;

public:
    Segment& operator+=(const Vector &v);
    Segment& operator-=(const Vector &v);

public:
    Point p1, p2;

};

Segment operator+(const Segment &s, const Vector &v);
Segment operator-(const Segment &s, const Vector &v);

bool intersecting(const Line2P &l, const Segment &s);
bool strict_intersecting(const Line2P &l, const Segment &s);
bool intersecting(const Line &l, const Segment &s);
bool strict_intersecting(const Line &l, const Segment &s);
bool intersecting(const Segment &s1, const Segment &s2);

}

#endif // _CG2D_SEGMENT_H_
