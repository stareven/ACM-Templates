#include "utils.h"

namespace cg2d {

const double EPS = 1e-8;
const double PI = acos(-1.0);


bool eq0(double x) { return fabs(x) < EPS; }
bool ne0(double x) { return fabs(x) > EPS; }
bool lt0(double x) { return x < -EPS; }
bool le0(double x) { return x < EPS; }
bool gt0(double x) { return x > EPS; }
bool ge0(double x) { return x > -EPS; }

}
