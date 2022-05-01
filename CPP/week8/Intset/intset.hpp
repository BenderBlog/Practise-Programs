#ifndef _INTSET_
#define _INTSET_
#ifndef _IOSTREAM_
#include <iostream>
#endif
#ifndef _SET_
#include <set>
#endif
#ifndef _ALGORITHM_
#include <algorithm>
#endif

namespace superbart
{
    using namespace std;

    class Intset
    {
    public:
        set<int> m_intset;
        Intset();
        Intset(set<int> a);
        ~Intset();
        bool printSet();
        bool insert(int a);
        bool remove(int a);
        bool isEmpty();
        bool isHere(int a);
        void writeSet(set<int>& a);
        Intset getUnion(Intset a);
        Intset getIntersection(Intset a);
        Intset getSymmetricDifference(Intset a);
    };
}
#endif
