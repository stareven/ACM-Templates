#ifndef _CG2D_LINE_H_
#define _CG2D_LINE_H_

namespace cg2d {

class Point;

class Line
{
public:
    explicit Line();
    explicit Line(double _a, double _b, double _c);
    explicit Line(const Point &p1, const Point &p2);

public:
    double substitude(const Point &p) const;
    double distance(const Point &p) const;

public:
    double a, b, c;

};

bool parallel(const Line &l1, const Line &l2);
bool collinear(const Line &l1, const Line &l2);
bool intersecting(const Line &l1, const Line &l2);
Point intersection(const Line &l1, const Line &l2);

bool on(const Line &l, const Point &p);
bool counterclockwise(const Line &l, const Point &p);
bool clockwise(const Line &l, const Point &p);

}

#endif // _CG2D_LINE_H_
