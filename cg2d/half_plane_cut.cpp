#include "half_plane_cut.h"
#include "utils.h"
#include "Point.h"
#include "Line.h"
#include "Segment.h"

namespace cg2d {

using namespace std;

static void uniq_push_back(vector<Point> &ps, const Point &p)
{
    if (ps.empty() || ps.back() != p) ps.push_back(p);
}

vector<Point> half_plane_cut(const vector<Point> &points, const Line &cut)
{
    vector<Point> remains;
    do {
        remains.reserve(points.size());
        if (points.empty()) break;
        if (points.size() == 1) {
            if (!clockwise(cut, points.front()))
                remains.push_back(points.front());
            break;
        }
        for (size_t i = 1; i < points.size(); i++) {
            Segment seg(points[i - 1], points[i]);
            if (strict_intersecting(cut, seg))
                uniq_push_back(
                        remains, intersection(Line(seg.p1, seg.p2), cut));
            if (!clockwise(cut, seg.p2)) remains.push_back(seg.p2);
        }
        Segment seg(points.back(), points.front());
        if (strict_intersecting(cut, seg))
            uniq_push_back(
                    remains, intersection(Line(seg.p1, seg.p2), cut));
        if (!clockwise(cut, seg.p2)) remains.push_back(seg.p2);
    } while (false);
    return remains;

}


}
