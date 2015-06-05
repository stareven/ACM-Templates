#include "SparseTable.h"
#include <assert.h>

namespace ds {

using namespace std;

SparseTable::SparseTable(const vector<int> &a)
{
    initialize(a);
}

SparseTable::~SparseTable()
{
}

int SparseTable::query(size_t left, size_t right) const
{
    assert(left != right);
    if (left > right) swap(left, right);
    assert(right <= _st.front().size());
    if (right - left == 1) return _st.front()[left];
    size_t level = 0;
    size_t half = 1;
    for (size_t len = half << 1; len < right - left; half = len, len <<= 1) level++;
    return min(_st[level][left], _st[level][right - half]);
}

void SparseTable::initialize(const vector<int> &a)
{
    _st.reserve(20);
    _st.push_back(a);
    for (size_t level = 1, len = 2, half = 1; len <= a.size(); level++, half = len, len <<= 1) {
        vector<int> &lower = _st.back();
        _st.push_back(vector<int>());
        vector<int> &upper = _st.back();
        upper.reserve(lower.size());
        for (size_t i = 0; i + len <= a.size(); i++)
            upper.push_back(min(lower[i], lower[i + half]));
    }
}

}
