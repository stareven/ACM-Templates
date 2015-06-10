#include "FenwickTree.h"
#include <assert.h>

namespace ds {

using namespace std;

FenwickTree::FenwickTree(size_t upper)
{
    assert(upper > 0);
    while (upper > lowbit(upper)) upper += lowbit(upper);
    _tree.resize(upper + 1);
}

FenwickTree::~FenwickTree()
{
}

void FenwickTree::update(size_t x, int inc)
{
    assert(x < _tree.size());
    for (size_t i = x; i < _tree.size(); i += lowbit(i)) _tree[i] += inc;
}

int FenwickTree::query(size_t x)
{
    assert(x < _tree.size());
    int sum = 0;
    for (size_t i = x; i > 0; i -= lowbit(i)) sum += _tree[i];
    return sum;
}

size_t FenwickTree::bsearch(int x)
{
    assert(_tree.back() >= x);
    size_t cnt = 0;
    int sum = 0;
    for (size_t i = _tree.size() - 1; i > 0; i >>= 1) {
        if (sum + _tree[cnt + i] >= x) continue;
        sum += _tree[cnt += i];
    }
    return cnt + 1;
}

}
