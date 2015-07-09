#ifndef _GT_MAXFLOW_GRAPH_H_
#define _GT_MAXFLOW_GRAPH_H_

#include <vector>

namespace gt { namespace maxflow {

class Graph
{
    struct Edge {
        int to;
        int cap;
        int next;
    };

public:
    explicit Graph(int n_vertices, int src, int dst, int n_edges=0);

public:
    void addEdge(int from, int to, int cap, int inv_cap=0);

public:
    int vertexCount() const;
    int src() const;
    int dst() const;

public:
    int head(int v) const;
    int from(int e) const;
    int to(int e) const;
    int cap(int e) const;
    int next(int e) const;
    int inverse(int e) const;
    bool valid(int e) const;

public:
    void push(int e, int flow);

private:
    void doAddEdge(int from, int to, int cap);

private:
    std::vector<int> _heads;
    std::vector<Edge> _edges;
    int _src;
    int _dst;

};

}}

#endif // _GT_MAXFLOW_GRAPH_H_
