#ifndef _DS_SEG_TREE_SEG_TREE_HPP_
#define _DS_SEG_TREE_SEG_TREE_HPP_

#include <vector>

namespace ds {

template<typename T>
class SegTree
{
public:
    struct Node {
        int left, right;
        T t;
    };
    class Policy
    {
    protected:
        typedef Node SegNode;
    public:
        virtual ~Policy() {}
    public:
        virtual void initialize(SegNode &v) = 0;
        virtual void update(SegNode &orig, const T &t) = 0;
        virtual void push(SegNode &v, SegNode &lc, SegNode &rc) = 0;
        virtual void pull(SegNode &v, SegNode &lc, SegNode &rc) = 0;
        virtual T merge(const T &lc, const T &rc) = 0;

    };

public:
    explicit SegTree(int left, int right, Policy *policy);
    ~SegTree();

public:
    void update(int left, int right, const T& t);
    T query(int left, int right);

private:
    void build(int v, int left, int right);
    void doUpdate(int v, int left, int right, const T &t);
    T doQuery(int v, int left, int right);

private:
    std::vector<Node> _nodes;
    Policy *_policy;

};

}

#include "SegTree.ipp"

#endif // _DS_SEG_TREE_SEG_TREE_HPP_
