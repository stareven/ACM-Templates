#ifndef _CG2D_DEBUG_H_
#define _CG2D_DEBUG_H_

#include <ostream>

namespace cg2d {

class Vector;
class Point;
class Line2P;
class Line;
class Segment;

std::ostream& operator<<(std::ostream &out, const Vector &v);
std::ostream& operator<<(std::ostream &out, const Point &p);
std::ostream& operator<<(std::ostream &out, const Line2P &l);
std::ostream& operator<<(std::ostream &out, const Line &l);
std::ostream& operator<<(std::ostream &out, const Segment &s);


}

#endif // _CG2D_DEBUG_H_
