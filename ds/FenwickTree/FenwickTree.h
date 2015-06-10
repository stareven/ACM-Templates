#ifndef _DS_FENWICK_TREE_FENWICK_TREE_H_
#define _DS_FENWICK_TREE_FENWICK_TREE_H_

#include <vector>
#include <stdlib.h>

namespace ds {

class FenwickTree
{
public:
    explicit FenwickTree(size_t upper);
    ~FenwickTree();

public:
    void update(size_t x, int inc);
    int query(size_t x);
    size_t bsearch(int x);

private:
    static size_t lowbit(size_t x) { return -x & x; }

private:
    std::vector<int> _tree;

};

}

#endif // _DS_FENWICK_TREE_FENWICK_TREE_H_
