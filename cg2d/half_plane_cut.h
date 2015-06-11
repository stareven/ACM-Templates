#ifndef _CG2D_HALF_PLANE_CUT_H_
#define _CG2D_HALF_PLANE_CUT_H_

#include <vector>

namespace cg2d {

class Point;
class Line;

std::vector<Point> half_plane_cut(const std::vector<Point> &points, const Line &cut);

}

#endif // _CG2D_HALF_PLANE_CUT_H_
