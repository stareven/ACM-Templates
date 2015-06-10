#include "SuffixArray.h"
#include <assert.h>
#include <string.h>
#include <map>
#include <algorithm>

namespace ds {

using namespace std;

SuffixArray::SuffixArray(const vector<int> &r, SAAlgo *algo)
    : _algo(algo)
{
    assert(_algo);
    initialize(r);
    run();
}

SuffixArray::SuffixArray(const string &s, SAAlgo *algo)
    : _algo(algo)
{
    assert(_algo);
    initialize(s);
    run();
}

SuffixArray::~SuffixArray()
{
    if (_algo) delete _algo;
}

template<typename TContainer>
void SuffixArray::initialize(const TContainer &r)
{
    _r.reserve(r.size() + 1);
    _r.assign(r.begin(), r.end());
    map<int, int> hash;
    _sigma = 1;
    for (vector<int>::const_iterator cit = _r.begin(); cit != _r.end(); cit++) hash[*cit] = _sigma;
    for (map<int, int>::iterator now = hash.begin(); now != hash.end(); now++) now->second = _sigma++;
    for (size_t i = 0; i < _r.size(); i++) _r[i] = hash[_r[i]];
    _r.push_back(0);
}

void SuffixArray::run()
{
    _sa.resize(_r.size());
    _rank.resize(_r.size());
    _algo->run(_r.data(), _sa.data(), _rank.data(), _r.size(), _sigma);
    calcHeight();
}

void SuffixArray::calcHeight()
{
    int n = _r.size();
    _height.resize(n);
    for (int i = 0, k = 0; i + 1 < n; i++, k -= k > 0) {
        while (_r[i + k] == _r[_sa[_rank[i] - 1] + k]) k++;
        _height[_rank[i]] = k;
    }
}

/*********************************************************************
 ** DAAlgo*
 ********************************************************************/

void SAAlgo::sort(const int *r, const int *s, int *t, int length, int *cnt, int sigma)
{
    memset(cnt, 0, sizeof(int) * sigma);
    for (int i = 0; i < length; i++) cnt[r[s[i]]]++;
    for (int j = 1; j < sigma; j++) cnt[j] += cnt[j - 1];
    for (int i = length - 1; i >= 0; i--) t[--cnt[r[s[i]]]] = s[i];
}

bool SAAlgoDA::equal(const int *r, int len, int x, int y)
{
    return r[x] == r[y] && r[x + len] == r[y + len];
}

void SAAlgoDA::run(const int *r, int *sa, int *rank, int length, int sigma)
{
    int *buf = new int[length * 3];
    int *cnt = buf;
    int *p_rank = cnt + length;
    int *n_rank = p_rank + length;
    int *p_sa = p_rank;
    memcpy(n_rank, r, sizeof(int) * length);
    for (int i = 0; i < length; i++) p_sa[i] = i;
    sort(n_rank, p_sa, sa, length, cnt, sigma);
    for (int len = 1; sigma < length; len <<= 1) {
        swap(p_rank, n_rank);
        p_sa = n_rank;
        int p = 0;
        for (int i = length - len; i < length; i++) p_sa[p++] = i;
        for (int i = 0; i < length; i++) if (sa[i] >= len) p_sa[p++] = sa[i] - len;
        sort(p_rank, p_sa, sa, length, cnt, sigma);
        sigma = 0;
        n_rank[sa[0]] = sigma++;
        for (int i = 1; i < length; i++)
            n_rank[sa[i]] = equal(p_rank, len, sa[i - 1], sa[i])? sigma - 1 : sigma++;
    }
    memcpy(rank, n_rank, sizeof(int) * length);
    delete[] buf;
}

void SAAlgoDC3::run(const int *r, int *sa, int *rank, int length, int sigma)
{
    int *buf = new int[length * 12];
    _cnt = buf;
    _r = _cnt + length;
    _sa = _r + length * 3;
    _sa0 = _sa + length * 3;
    _sa12 = _sa0 + length;
    _rank12 = _sa12 + length;
    memcpy(_r, r, sizeof(int) * length);
    doRun(_r, _sa, length, sigma);
    memcpy(sa, _sa, sizeof(int) * length);
    for (int i = 0; i < length; i++) rank[sa[i]] = i;
    delete[] buf;
}

void SAAlgoDC3::doRun(int *r, int *sa, int length, int sigma)
{
#define F(x) ((x) / 3 + ((x) % 3 == 1? 0 : len1))
#define rF(x) ((x) < len1? ((x) * 3 + 1) : (((x) - len1) * 3 + 2))
    // sa of: i % 3 != 0
    int len12 = 0, len1 = (length + 1) / 3;
    for (int i = 0; i < length; i++) if (i % 3) _sa0[len12++] = i;
    r[length] = r[length + 1] = 0;
    sort(r + 2, _sa0, _sa12, len12, _cnt, sigma);
    sort(r + 1, _sa12, _sa0, len12, _cnt, sigma);
    sort(r, _sa0, _sa12, len12, _cnt, sigma);
    int *n_r = r + length, *n_sa = sa + length;
    int n_sigma = 0;
    n_r[F(_sa12[0])] = n_sigma++;
    for (int i = 1; i < len12; i++)
        n_r[F(_sa12[i])] = equal(r, _sa12[i - 1], _sa12[i])? n_sigma - 1 : n_sigma++;
    if (n_sigma < len12) doRun(n_r, n_sa, len12, n_sigma);
    else for (int i = 0; i < len12; i++) n_sa[n_r[i]] = i;
    // sa of: i % 3 == 0
    int len0 = 0;
    if (length % 3 == 1) _sa12[len0++] = length - 1;
    for (int i = 0; i < len12; i++)
        if (n_sa[i] < len1)
            _sa12[len0++] = n_sa[i] * 3;
    sort(r, _sa12, _sa0, len0, _cnt, sigma);
    for (int i = 0; i < len12; i++) _sa12[i] = rF(n_sa[i]);
    for (int i = 0; i < len12; i++) _rank12[_sa12[i]] = i;
    // merge
    int k = 0, i = 0, j = 0;
    while (i < len0 && j < len12)
        sa[k++] = cmp(_sa12[j] % 3, r, _sa0[i], _sa12[j])? _sa0[i++] : _sa12[j++];
    while (i < len0) sa[k++] = _sa0[i++];
    while (j < len12) sa[k++] = _sa12[j++];
#undef F
#undef rF
}

bool SAAlgoDC3::equal(const int *r, int x, int y)
{
    return r[x] == r[y] && r[x + 1] == r[y + 1] && r[x + 2] == r[y + 2];
}

bool SAAlgoDC3::cmp(int t, const int *r, int x, int y)
{
    if (r[x] != r[y]) return r[x] < r[y];
    if (t == 1) return _rank12[x + 1] < _rank12[y + 1];
    else return cmp(1, r, x + 1, y + 1);
}

}
