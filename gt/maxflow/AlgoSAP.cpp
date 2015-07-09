#include "AlgoSAP.h"
#include "Graph.h"

namespace gt { namespace maxflow {

using namespace std;

AlgoSAP::AlgoSAP(Graph &g)
    : Algo(g)
{
}

int AlgoSAP::run()
{
    initialize();
    int maxflow = 0;
    while (_label[_g.src()] < _g.vertexCount())
        maxflow += augment(_g.src());
    return maxflow;
}

void AlgoSAP::initialize()
{
    _label.assign(_g.vertexCount(), 0);
    _gap.assign(_g.vertexCount() + 1, 0);
    _gap[0] = _g.vertexCount();
}

int AlgoSAP::augment(int from, int neck)
{
    if (from == _g.dst()) return neck;
    int maxflow = 0;
    for (int e = _g.head(from); _g.valid(e); e = _g.next(e)) {
        if (maxflow == neck) return maxflow;
        int to = _g.to(e);
        int cap = _g.cap(e);
        if (!cap || _label[to] + 1 != _label[from]) continue;
        int flow = augment(to, min(neck - maxflow, cap));
        _g.push(e, flow);
        maxflow += flow;
    }
    if (!--_gap[_label[from]++]) _label[_g.src()] = _g.vertexCount();
    _gap[_label[from]]++;
    return maxflow;
}

}}
