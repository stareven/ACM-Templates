#include "Point.h"
#include "utils.h"
#include "Vector.h"

namespace cg2d {

Point::Point()
    : x(0), y(0)
{
}

Point::Point(double x_, double y_)
    : x(x_), y(y_)
{
}


Point& Point::operator+=(const Vector &v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Point& Point::operator-=(const Vector &v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}


bool operator==(const Point &p1, const Point &p2)
{
    return eq0(p1.x - p2.x) && eq0(p1.y - p2.y);
}

bool operator!=(const Point &p1, const Point &p2)
{
    return !(p1 == p2);
}

bool operator<(const Point &p1, const Point &p2)
{
    if (ne0(p1.y - p2.y)) return lt0(p1.y - p2.y);
    return lt0(p1.x - p2.x);
}

Vector operator-(const Point &p1, const Point &p2)
{
    return Vector(p1.x - p2.x, p1.y - p2.y);
}

Point operator+(const Point &p, const Vector &v)
{
    return Point(p) += v;
}

Point operator-(const Point &p, const Vector &v)
{
    return Point(p) -= v;
}

}
