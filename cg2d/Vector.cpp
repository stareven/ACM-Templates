#include "Vector.h"
#include "utils.h"

namespace cg2d {

Vector::Vector()
    : x(0), y(0)
{
}

Vector::Vector(double x_, double y_)
    : x(x_), y(y_)
{
}


bool Vector::vertical() const
{
    return eq0(x);
}

bool Vector::horizontal() const
{
    return eq0(y);
}

double Vector::squaredLength() const
{
    return x * x + y * y;
}

double Vector::length() const
{
    return sqrtl(squaredLength());
}

double Vector::slope() const
{
    return y / x;
}

Vector Vector::normal() const
{
    return (1.0 / length()) * Vector(-y, x);
}


Vector& Vector::operator+=(const Vector &v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector& Vector::operator-=(const Vector &v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector& Vector::operator*=(double r)
{
    x *= r;
    y *= r;
    return *this;
}

Vector& Vector::operator/=(double r)
{
    *this *= 1 / r;
    return *this;
}


Vector operator+(const Vector &v1, const Vector &v2)
{
    return Vector(v1) += v2;
}

Vector operator-(const Vector &v1, const Vector &v2)
{
    return Vector(v1) -= v2;
}

Vector operator*(const Vector &v, double r)
{
    return Vector(v) *= r;
}

Vector operator*(double r, const Vector &v)
{
    return v * r;
}

Vector operator/(const Vector &v, double r)
{
    return Vector(v) /= r;
}

double operator*(const Vector &v1, const Vector &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

double operator^(const Vector &v1, const Vector &v2)
{
    return v1.x * v2.y - v2.x * v1.y;
}

bool collinear(const Vector &v1, const Vector &v2)
{
    return eq0(v1 ^ v2);
}

bool counterclockwise(const Vector &v1, const Vector &v2)
{
    return gt0(v1 ^ v2);
}

bool clockwise(const Vector &v1, const Vector &v2)
{
    return lt0(v1 ^ v2);
}


}
