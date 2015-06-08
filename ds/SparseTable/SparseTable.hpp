#ifndef _DS_SPARSE_TABLE_HPP_
#define _DS_SPARSE_TABLE_HPP_

#include <stdlib.h>
#include <vector>
#include <functional>

namespace ds {

template<typename T, typename TCompare=std::less<T> >
class SparseTable
{
    static TCompare _compare;
public:
    explicit SparseTable(const std::vector<T> &a);

public:
    T query(size_t left, size_t right) const;

private:
    void initialize(const std::vector<T> &a);

private:
    std::vector<std::vector<T> > _st;

};

}

#include "SparseTable.ipp"

#endif // _DS_SPARSE_TABLE_HPP_
