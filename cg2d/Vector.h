#ifndef _CG2D_VECTOR_H_
#define _CG2D_VECTOR_H_

namespace cg2d {

class Vector
{
public:
    explicit Vector();
    explicit Vector(double x_, double y_);

public:
    bool vertical() const;
    bool horizontal() const;
    double squaredLength() const;
    double length() const;
    double slope() const;
    Vector normal() const;

public:
    Vector& operator+=(const Vector &v);
    Vector& operator-=(const Vector &v);
    Vector& operator*=(double r);
    Vector& operator/=(double r);

public:
    double x, y;

};

Vector operator+(const Vector &v1, const Vector &v2);
Vector operator-(const Vector &v1, const Vector &v2);
Vector operator*(const Vector &v, double r);
Vector operator*(double r, const Vector &v);
Vector operator/(const Vector &v, double r);
double operator*(const Vector &v1, const Vector &v2);
double operator^(const Vector &v1, const Vector &v2);
bool collinear(const Vector &v1, const Vector &v2);
bool counterclockwise(const Vector &v1, const Vector &v2);
bool clockwise(const Vector &v1, const Vector &v2);

}

#endif // _CG2D_VECTOR_H_
