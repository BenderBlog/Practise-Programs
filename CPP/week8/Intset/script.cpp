#include "intset.hpp"

using namespace superbart;

int main()
{
    set<int> toInit;

    toInit = {1,2,3,5,8,0};
    Intset homer(toInit);

    toInit = {2,4,5,6,9};
    Intset marge(toInit);

    Intset bart = marge.getUnion(homer);
    Intset lisa = marge.getIntersection(homer);
    Intset maggie = marge.getSymmetricDifference(homer);

    cout << "Set one: " << endl;
    homer.printSet();
    cout << "Set two: " << endl;
    marge.printSet();
    cout << "Union: " << endl;
    bart.printSet();
    cout << "Intersection: " << endl;
    lisa.printSet();
    cout << "Symmmetric Difference: " << endl;
    maggie.printSet();
}
