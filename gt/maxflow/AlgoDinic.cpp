#include "AlgoDinic.h"
#include <limits>
#include <queue>
#include "Graph.h"

namespace gt { namespace maxflow {

using namespace std;

AlgoDinic::AlgoDinic(Graph &g)
    : Algo(g)
{
}

int AlgoDinic::run()
{
    _arc.assign(_g.vertexCount(), -1);
    int maxflow = 0;
    while (relabel()) {
        resetCurrentArc();
        maxflow += augment(_g.src());
    }
    return maxflow;
}

bool AlgoDinic::relabel()
{
    _label.assign(_g.vertexCount(), -1);
    _label[_g.src()] = 0;
    queue<int> q;
    q.push(_g.src());
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (int e = _g.head(from); _g.valid(e); e = _g.next(e)) {
            int to = _g.to(e);
            if (!_g.cap(e) || ~_label[to]) continue;
            _label[to] = _label[from] + 1;
            if (to == _g.dst()) return true;
            q.push(to);
        }
    }
    return false;
}

void AlgoDinic::resetCurrentArc()
{
    for (int v = 0; v < _g.vertexCount(); v++) _arc[v] = _g.head(v);
}

int AlgoDinic::augment(int from, int neck)
{
    if (from == _g.dst()) return neck;
    int maxflow = 0;
    for (int e = _arc[from]; _g.valid(e); _arc[from] = e = _g.next(e)) {
        if (maxflow == neck) return maxflow;
        int to = _g.to(e);
        int cap = _g.cap(e);
        if (!cap || _label[to] <= _label[from]) continue;
        int flow = augment(to, min(neck - maxflow, cap));
        _g.push(e, flow);
        maxflow += flow;
    }
    return maxflow;
}

}}
