#ifndef _DS_SEG_TREE_SEG_TREE_IPP_
#define _DS_SEG_TREE_SEG_TREE_IPP_

#include "SegTree.hpp"
#include <assert.h>
#include <stdlib.h>

namespace ds {

template<typename T>
SegTree<T>::SegTree(int left, int right, Policy *policy)
    : _policy(policy)
{
    assert(policy);
    assert(left < right);
    _nodes.resize((right - left) << 2);
    build(0, left, right);
}

template<typename T>
SegTree<T>::~SegTree()
{
    if (_policy) {
        delete _policy;
        _policy = NULL;
    }
}

template<typename T>
void SegTree<T>::update(int left, int right, const T& t)
{
    doUpdate(0, left, right, t);
}

template<typename T>
T SegTree<T>::query(int left, int right)
{
    return doQuery(0, left, right);
}

template<typename T>
void SegTree<T>::build(int v, int left, int right)
{
    _nodes[v].left = left;
    _nodes[v].right = right;
    if (right - left == 1) {
        _policy->initialize(_nodes[v]);
        return;
    }
    int mid = (left + right) >> 1;
    int lc = (v << 1) + 1, rc = lc + 1;
    build(lc, left, mid);
    build(rc, mid, right);
    _policy->pull(_nodes[v], _nodes[lc], _nodes[rc]);
}

template<typename T>
void SegTree<T>::doUpdate(int v, int left, int right, const T& t)
{
    if (left == _nodes[v].left && right == _nodes[v].right) {
        _policy->update(_nodes[v], t);
        return;
    }
    int mid = (_nodes[v].left + _nodes[v].right) >> 1;
    int lc = (v << 1) + 1, rc = lc + 1;
    _policy->push(_nodes[v], _nodes[lc], _nodes[rc]);
    if (right <= mid) doUpdate(lc, left, right, t);
    else if (left >= mid) doUpdate(rc, left, right, t);
    else doUpdate(lc, left, mid, t), doUpdate(rc, mid, right, t);
    _policy->pull(_nodes[v], _nodes[lc], _nodes[rc]);
}

template<typename T>
T SegTree<T>::doQuery(int v, int left, int right)
{
    if (left == _nodes[v].left && right == _nodes[v].right) return _nodes[v].t;
    int mid = (_nodes[v].left + _nodes[v].right) >> 1;
    int lc = (v << 1) + 1, rc = lc + 1;
    _policy->push(_nodes[v], _nodes[lc], _nodes[rc]);
    if (right <= mid) return doQuery(lc, left, right);
    else if (left >= mid) return doQuery(rc, left, right);
    else return _policy->merge(doQuery(lc, left, mid), doQuery(rc, mid, right));
}

}

#endif // _DS_SEG_TREE_SEG_TREE_IPP_
