#ifndef _GT_MAXFLOW_ALGO_DINIC_H_
#define _GT_MAXFLOW_ALGO_DINIC_H_

#include <limits>
#include <vector>
#include "Algo.h"

namespace gt { namespace maxflow {

class AlgoDinic: public Algo
{
public:
    explicit AlgoDinic(Graph &g);

public:
    virtual int run();

private:
    bool relabel();
    void resetCurrentArc();
    int augment(int from, int neck=std::numeric_limits<int>::max());

private:
    std::vector<int> _label;    // distance label
    std::vector<int> _arc;      // current arc

};

}}


#endif // _GT_MAXFLOW_ALGO_DINIC_H_
