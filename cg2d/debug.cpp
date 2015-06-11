#include "debug.h"
#include "Vector.h"
#include "Point.h"
#include "Line2P.h"
#include "Line.h"
#include "Segment.h"

namespace cg2d {

using namespace std;

ostream& operator<<(ostream &out, const Vector &v)
{
    out << "v<" << v.x << ", " << v.y << ">";
    return out;
}

ostream& operator<<(ostream &out, const Point &p)
{
    out << "p<" << p.x << ", " << p.y << ">";
    return out;
}

ostream& operator<<(ostream &out, const Line2P &l)
{
    out << "l2p<" << l.p1 << ", " << l.p2 << ">";
    return out;
}

ostream& operator<<(ostream &out, const Line &l)
{
    out << "l<" << l.a << "x + " << l.b << "y + " << l.c << " = 0>";
    return out;
}

ostream& operator<<(ostream &out, const Segment &s)
{
    out << "s<" << s.p1 << ", " << s.p2 << ">";
    return out;
}

}
