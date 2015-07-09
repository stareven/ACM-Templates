#ifndef _GT_MAXFLOW_ALGO_EDMOND_KARP_H_
#define _GT_MAXFLOW_ALGO_EDMOND_KARP_H_

#include <vector>
#include "Algo.h"

namespace gt { namespace maxflow {

class AlgoEdmondKarp: public Algo
{
public:
    explicit AlgoEdmondKarp(Graph &g);

public:
    virtual int run();

private:
    int augment();
    bool findPath();
    int findNeck();
    void push(int flow);

private:
    std::vector<int> _via;

};

}}

#endif // _GT_MAXFLOW_ALGO_EDMOND_KARP_H_
