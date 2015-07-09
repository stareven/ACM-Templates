#include "Graph.h"

namespace gt { namespace maxflow {

Graph::Graph(int n_vertices, int src, int dst, int n_edges)
    : _heads(n_vertices, -1), _src(src), _dst(dst)
{
    _edges.reserve(n_edges);
}

void Graph::addEdge(int from, int to, int cap, int inv_cap)
{
    doAddEdge(from, to, cap);
    doAddEdge(to, from, inv_cap);
}

int Graph::vertexCount() const
{
    return _heads.size();
}

int Graph::src() const
{
    return _src;
}

int Graph::dst() const
{
    return _dst;
}

int Graph::head(int v) const
{
    return _heads[v];
}

int Graph::from(int e) const
{
    return to(inverse(e));
}

int Graph::to(int e) const
{
    return _edges[e].to;
}

int Graph::cap(int e) const
{
    return _edges[e].cap;
}

int Graph::next(int e) const
{
    return _edges[e].next;
}

int Graph::inverse(int e) const
{
    return e ^ 1;
}

bool Graph::valid(int e) const
{
    return ~e;
}

void Graph::push(int e, int flow)
{
    _edges[e].cap -= flow;
    _edges[inverse(e)].cap += flow;
}

void Graph::doAddEdge(int from, int to, int cap)
{
    Edge e;
    e.to = to;
    e.cap = cap;
    e.next = _heads[from];
    _heads[from] = _edges.size();
    _edges.push_back(e);
}

}}
