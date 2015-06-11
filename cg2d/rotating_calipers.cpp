#include "rotating_calipers.h"
#include <algorithm>
#include "Vector.h"
#include "Point.h"
#include "Line.h"
#include "Segment.h"

namespace cg2d {

using namespace std;

void rotating_calipers(const vector<Point> &c_a, const vector<Point> &c_b, RotatingCalipersPolicy &policy)
{
    if (c_a.empty() || c_b.empty()) return;
    size_t o_a = min_element(c_a.begin(), c_a.end()) - c_a.begin();
    size_t o_b = max_element(c_b.begin(), c_b.end()) - c_b.begin();
    for (size_t i = 0, j = 0; i < c_a.size(); i++) {
        Segment seg_a(
                c_a[(o_a + i) % c_a.size()],
                c_a[(o_a + i + 1) % c_a.size()]);
        Vector v_a = seg_a.p2 - seg_a.p1;
        do {
            Vector v_b =
                c_b[(o_b + j + 1) % c_b.size()] -
                c_b[(o_b + j) % c_b.size()];
            if (!counterclockwise(v_a, v_b)) break;
            j++;
        } while (true);
        Segment seg_b(
                c_b[(o_b + j) % c_b.size()],
                c_b[(o_b + j + 1) % c_b.size()]);
        policy.processAntipodals(seg_a, seg_b);
    }
}

}
