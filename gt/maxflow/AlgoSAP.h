#ifndef _GT_MAXFLOW_ALGO_SAP_H_
#define _GT_MAXFLOW_ALGO_SAP_H_

#include <limits>
#include <vector>
#include "Algo.h"

namespace gt { namespace maxflow {

class AlgoSAP: public Algo
{
public:
    explicit AlgoSAP(Graph &g);

public:
    virtual int run();

private:
    void initialize();
    int augment(int from, int neck=std::numeric_limits<int>::max());

private:
    std::vector<int> _label;    // distance label
    std::vector<int> _gap;

};

}}

#endif // _GT_MAXFLOW_ALGO_SAP_H_
