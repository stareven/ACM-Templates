#ifndef _GT_MAXFLOW_ALGO_H_
#define _GT_MAXFLOW_ALGO_H_

namespace gt { namespace maxflow {

class Graph;

class Algo
{
public:
    explicit Algo(Graph &g): _g(g) {}
    virtual ~Algo() {}

public:
    virtual int run() = 0;

protected:
    Graph &_g;

};

}}

#endif // _GT_MAXFLOW_ALGO_H_
