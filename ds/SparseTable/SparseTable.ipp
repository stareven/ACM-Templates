#ifndef _DS_SPARSE_TABLE_IPP_
#define _DS_SPARSE_TABLE_IPP_

#include "SparseTable.hpp"
#include <assert.h>

namespace ds {

template<typename T, typename TCompare>
TCompare SparseTable<T, TCompare>::_compare;

template<typename T, typename TCompare>
SparseTable<T, TCompare>::SparseTable(const std::vector<T> &a)
{
    initialize(a);
}

template<typename T, typename TCompare>
T SparseTable<T, TCompare>::query(size_t left, size_t right) const
{
    assert(left != right);
    if (left > right) std::swap(left, right);
    assert(right <= _st.front().size());
    if (right - left == 1) return _st.front()[left];
    size_t level = 0;
    size_t half = 1;
    for (size_t len = half << 1; len < right - left; half = len, len <<= 1) level++;
    return min(_st[level][left], _st[level][right - half], _compare);
}

template<typename T, typename TCompare>
void SparseTable<T, TCompare>::initialize(const std::vector<T> &a)
{
    _st.reserve(20);
    _st.push_back(a);
    for (size_t level = 1, len = 2, half = 1; len <= a.size(); level++, half = len, len <<= 1) {
        std::vector<int> &lower = _st.back();
        _st.push_back(std::vector<int>());
        std::vector<int> &upper = _st.back();
        upper.reserve(a.size() - len + 1);
        for (size_t i = 0; i + len <= a.size(); i++)
            upper.push_back(min(lower[i], lower[i + half], _compare));
    }
}

}

#endif // _DS_SPARSE_TABLE_IPP_
