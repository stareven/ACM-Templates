#ifndef _DS_SEG_TREE_SEG_TREE_IPP_
#define _DS_SEG_TREE_SEG_TREE_IPP_

#include "SegTree.hpp"
#include <assert.h>
#include <stdlib.h>

namespace ds {

template<typename T, typename TStrategy>
struct SegTree<T, TStrategy>::Node
{
    int left, right;
    T t;
};

template<typename T, typename TStrategy>
SegTree<T, TStrategy>::SegTree(int left, int right, const T &t)
{
    assert(left < right);
    _nodes.resize((right - left) << 2);
    build(0, left, right, t);
}

template<typename T, typename TStrategy>
void SegTree<T, TStrategy>::update(int left, int right, const T& t)
{
    doUpdate(0, left, right, t);
}

template<typename T, typename TStrategy>
T SegTree<T, TStrategy>::query(int left, int right)
{
    return doQuery(0, left, right);
}

template<typename T, typename TStrategy>
void SegTree<T, TStrategy>::build(int v, int left, int right, const T& t)
{
    _nodes[v].left = left;
    _nodes[v].right = right;
    _nodes[v].t = t;
    if (right - left == 1) return;
    int mid = (left + right) >> 1;
    int lc = (v << 1) + 1, rc = lc + 1;
    build(lc, left, mid, t);
    build(rc, mid, right, t);
}

template<typename T, typename TStrategy>
void SegTree<T, TStrategy>::doUpdate(int v, int left, int right, const T& t)
{
    if (left == _nodes[v].left && right == _nodes[v].right) {
        TStrategy::update(_nodes[v].t, t);
        return;
    }
    int mid = (_nodes[v].left + _nodes[v].right) >> 1;
    int lc = (v << 1) + 1, rc = lc + 1;
    TStrategy::push(_nodes[v].t, _nodes[lc].t, _nodes[rc].t);
    if (right <= mid) doUpdate(lc, left, right, t);
    else if (left >= mid) doUpdate(rc, left, right, t);
    else doUpdate(lc, left, mid, t), doUpdate(rc, mid, right, t);
    TStrategy::pull(_nodes[v].t, _nodes[lc].t, _nodes[rc].t);
}

template<typename T, typename TStrategy>
T SegTree<T, TStrategy>::doQuery(int v, int left, int right)
{
    if (left == _nodes[v].left && right == _nodes[v].right) return _nodes[v].t;
    int mid = (_nodes[v].left + _nodes[v].right) >> 1;
    int lc = (v << 1) + 1, rc = lc + 1;
    TStrategy::push(_nodes[v].t, _nodes[lc].t, _nodes[rc].t);
    if (right <= mid) return doQuery(lc, left, right);
    else if (left >= mid) return doQuery(rc, left, right);
    else return TStrategy::merge(doQuery(lc, left, mid), doQuery(rc, mid, right));
}

}

#endif // _DS_SEG_TREE_SEG_TREE_IPP_
