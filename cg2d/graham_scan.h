#ifndef _CG2D_GRAHAM_SCAN_H_
#define _CG2D_GRAHAM_SCAN_H_

#include <vector>

namespace cg2d {

class Point;

// Warning: keep_passed=true && points forms a line
//      =>  size < 2 * points.size()
std::vector<Point> graham_scan(const std::vector<Point> &points, bool keep_passed=false);


}

#endif // _CG2D_GRAHAM_SCAN_H_
