#ifndef _UTIL_UTILS_H_
#define _UTIL_UTILS_H_

#include <ostream>
#include <vector>
#include <set>
#include <map>

namespace std {

template<typename T1, typename T2>
ostream& operator<<(ostream &out, const pair<T1, T2> &p)
{
    out << "p<" << p.first << ", " << p.second << ">";
    return out;
}

template<typename T>
ostream& operator<<(ostream &out, const vector<T> &v)
{
    out << "v<";
    for (size_t i = 0; i < v.size(); i++) out << i << ": " << v[i] << ", ";
    out << ">";
    return out;
}

template<typename T>
ostream& operator<<(ostream &out, const set<T> &s)
{
    out << "s<";
    for (typename set<T>::const_iterator
            cit = s.begin(); cit != s.end(); cit++)
        out << *cit << ", ";
    out << ">";
    return out;
}

template<typename TKey, typename TValue>
ostream& operator<<(ostream &out, const map<TKey, TValue> &m)
{
    out << "m<";
    for (typename map<TKey, TValue>::const_iterator
            cit = m.begin(); cit != m.end(); cit++)
        out << cit->first << ": " << cit->second << ", ";
    out << ">";
    return out;
}

}

namespace utils {

}

#endif // _UTIL_UTILS_H_
