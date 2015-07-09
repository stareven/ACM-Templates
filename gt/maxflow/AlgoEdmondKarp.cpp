#include "AlgoEdmondKarp.h"
#include <limits>
#include <queue>
#include "Graph.h"

namespace gt { namespace maxflow {

using namespace std;

AlgoEdmondKarp::AlgoEdmondKarp(Graph &g)
    : Algo(g)
{
}

int AlgoEdmondKarp::run()
{
    int maxflow = 0;
    while (int flow = augment()) maxflow += flow;
    return maxflow;
}

int AlgoEdmondKarp::augment()
{
    if (!findPath()) return 0;
    int flow = findNeck();
    push(flow);
    return flow;
}

bool AlgoEdmondKarp::findPath()
{
    _via.assign(_g.vertexCount(), -1);
    queue<int> q;
    q.push(_g.src());
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (int e = _g.head(from); _g.valid(e); e = _g.next(e)) {
            int to = _g.to(e);
            if (!_g.cap(e) || ~_via[to]) continue;
            _via[to] = e;
            if (to == _g.dst()) return true;
            q.push(to);
        }
    }
    return false;
}

int AlgoEdmondKarp::findNeck()
{
    int neck = numeric_limits<int>::max();
    for (int to = _g.dst(), from = -1; to != _g.src(); to = from) {
        int e = _via[to];
        from = _g.from(e);
        neck = min(neck, _g.cap(e));
    }
    return neck;
}

void AlgoEdmondKarp::push(int flow)
{
    for (int to = _g.dst(), from = -1; to != _g.src(); to = from) {
        int e = _via[to];
        from = _g.from(e);
        _g.push(e, flow);
    }
}

}}
