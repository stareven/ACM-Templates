#ifndef _CG2D_POINT_H_
#define _CG2D_POINT_H_

namespace cg2d {

class Vector;

class Point
{
public:
    explicit Point();
    explicit Point(double x_, double y_);

public:
    Point& operator+=(const Vector &v);
    Point& operator-=(const Vector &v);

public:
    double x, y;

};

bool operator==(const Point &p1, const Point &p2);
bool operator!=(const Point &p1, const Point &p2);
bool operator<(const Point &p1, const Point &p2);
Vector operator-(const Point &p1, const Point &p2);
Point operator+(const Point &p, const Vector &v);
Point operator-(const Point &p, const Vector &v);

}

#endif // _CG2D_POINT_H_
