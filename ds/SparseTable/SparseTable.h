#ifndef _DS_SPARSE_TABLE_H_
#define _DS_SPARSE_TABLE_H_

#include <stdlib.h>
#include <vector>

namespace ds {

class SparseTable
{
public:
    explicit SparseTable(const std::vector<int> &a);
    ~SparseTable();

public:
    int query(size_t left, size_t right) const;

private:
    void initialize(const std::vector<int> &a);

private:
    std::vector<std::vector<int> > _st;

};

}

#endif // _DS_SPARSE_TABLE_H_
