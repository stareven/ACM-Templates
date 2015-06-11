#ifndef _CG2D_ROTATING_CALIPERS_H_
#define _CG2D_ROTATING_CALIPERS_H_

#include <vector>

namespace cg2d {

class Point;
class Segment;

class RotatingCalipersPolicy
{
public:
    virtual void processAntipodals(const Segment &s1, const Segment &s2) = 0;
};

// Warning: use convex with keep_passed=false
void rotating_calipers(const std::vector<Point> &c_a, const std::vector<Point> &c_b, RotatingCalipersPolicy &policy);

}

#endif // _CG2D_ROTATING_CALIPERS_H_
