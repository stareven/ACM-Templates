#ifndef _DS_SUFFIX_ARRAY_H_
#define _DS_SUFFIX_ARRAY_H_

#include <vector>
#include <string>

namespace ds {

class SAAlgo
{
public:
    virtual ~SAAlgo() {}

public:
    virtual void run(const int *r, int *sa, int *rank, int length, int sigma) = 0;

protected:
    static void sort(const int *r, const int *s, int *t, int length, int *cnt, int sigma);
};

class SAAlgoDA: public SAAlgo
{
public:
    virtual void run(const int *r, int *sa, int *rank, int length, int sigma);

private:
    static bool equal(const int *r, int len, int x, int y);

};

class SAAlgoDC3: public SAAlgo
{
public:
    virtual void run(const int *r, int *sa, int *rank, int length, int sigma);

private:
    void doRun(int *r, int *sa, int length, int sigma);
    static bool equal(const int *r, int x, int y);
    bool cmp(int t, const int *r, int x, int y);

private:
    int *_cnt;
    int *_r;
    int *_sa;
    int *_sa0;
    int *_sa12;
    int *_rank12;

};

class SuffixArray
{
public:
    explicit SuffixArray(const std::vector<int> &r, SAAlgo *algo=new SAAlgoDA);
    explicit SuffixArray(const std::string &s, SAAlgo *algo=new SAAlgoDA);
    virtual ~SuffixArray();

public:
    const std::vector<int>& sa() const { return _sa; }
    int sa(int i) const { return _sa[i]; }
    const std::vector<int>& rank() const { return _rank; }
    int rank(int i) const { return _rank[i]; }
    const std::vector<int>& height() const { return _height; }
    int height(int i) const { return _height[i]; }

private:
    template<typename TContainer>
    void initialize(const TContainer &r);
    void run();
    void calcHeight();

private:
    int _sigma;
    std::vector<int> _r;
    SAAlgo *_algo;
    std::vector<int> _sa;
    std::vector<int> _rank;
    std::vector<int> _height;

};

}

#endif // _DS_SUFFIX_ARRAY_H_
