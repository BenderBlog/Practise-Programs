#include "intset.hpp"
namespace superbart
{
    bool Intset::isEmpty()
    {
        return m_intset.empty();
    }

    bool Intset::isHere(int a)
    {
        if (m_intset.find(a) != m_intset.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Intset::insert(int a)
    {
        if (!isHere(a))
        {
            m_intset.insert(a);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Intset::remove(int a)
    {
        if (isHere(a))
        {
            m_intset.erase(a);
            return true;
        }
        else
        {
            return false;
        }
    }

    Intset::Intset()
    {
    }

    Intset::Intset(set<int> a)
    {
        if (isEmpty() == true)
        {
            m_intset = a;
        }
        else
        {
            cout << "Set is not empty!" << endl;
        }
    }

    Intset::~Intset()
    {
        m_intset.clear();
    }

    bool Intset::printSet()
    {
        if (!isEmpty())
        {
            for (auto i : m_intset)
            {
                cout << i << " ";
            }
            cout << endl;
            return true;
        }
        else
        {
            return false;
        }
    }

    void Intset::writeSet(set<int>& a)
    {
        m_intset = a;
    }

    Intset Intset::getUnion(Intset a)
    {
        Intset getUnioned;
        set_union(std::begin(m_intset),
                  std::end(m_intset),
                  std::begin(a.m_intset),
                  std::end(a.m_intset),
                  std::inserter(getUnioned.m_intset,
                                getUnioned.m_intset.begin()));
        return getUnioned;
    }

    Intset Intset::getIntersection(Intset a)
    {
        Intset getIntersectioned;
        set_intersection(std::begin(m_intset),
                         std::end(m_intset),
                         std::begin(a.m_intset),
                         std::end(a.m_intset),
                         std::inserter(getIntersectioned.m_intset,
                                       getIntersectioned.m_intset.begin()));
        return getIntersectioned;
    }

    Intset Intset::getSymmetricDifference(Intset a)
    {
        Intset getSymmetricDifferenced;
        set_symmetric_difference(std::begin(m_intset),
                                 std::end(m_intset),
                                 std::begin(a.m_intset),
                                 std::end(a.m_intset),
                                 std::inserter(getSymmetricDifferenced.m_intset,
                                                    getSymmetricDifferenced.m_intset.begin()));
        return getSymmetricDifferenced;
    }
}
