#ifndef _DS_SEG_TREE_SEG_TREE_HPP_
#define _DS_SEG_TREE_SEG_TREE_HPP_

#include <vector>

namespace ds {

template<typename T, typename TStrategy>
class SegTree
{
    struct Node;
public:
    explicit SegTree(int left, int right, const T &t=T());

public:
    void update(int left, int right, const T& t);
    T query(int left, int right);

private:
    void build(int v, int left, int right, const T &t);
    void doUpdate(int v, int left, int right, const T &t);
    T doQuery(int v, int left, int right);

private:
    std::vector<Node> _nodes;

};

}

#include "SegTree.ipp"

#endif // _DS_SEG_TREE_SEG_TREE_HPP_
