#include "graham_scan.h"
#include <assert.h>
#include <algorithm>
#include "Point.h"
#include "Vector.h"

namespace cg2d {

using namespace std;

template<typename TIterator>
static void scan(const TIterator &begin, const TIterator &end, bool keep_passed, vector<Point> &convex)
{
    size_t btm = convex.size();
    for (TIterator it = begin; it != end; it++) {
        while (convex.size() > btm) {
            Vector v1 = convex[convex.size() - 1] - convex[convex.size() - 2];
            Vector v2 = *it - convex[convex.size() - 2];
            if (counterclockwise(v1, v2)) break;
            if (keep_passed && collinear(v1, v2)) break;
            convex.pop_back();
        }
        convex.push_back(*it);
    }
}

vector<Point> graham_scan(const vector<Point> &points, bool keep_passed)
{
    vector<Point> convex;
    do {
        if (points.empty()) return convex;
        vector<Point> sorted(points);
        sort(sorted.begin(), sorted.end());
        convex.reserve(sorted.size());
        convex.push_back(sorted.front());
        scan(sorted.begin() + 1, sorted.end(), keep_passed, convex);
        scan(sorted.rbegin() + 1, sorted.rend(), keep_passed, convex);
        assert(convex.size() != 2);
        if (convex.size() >= 3) convex.pop_back();
    } while (false);
    return convex;
}

}
