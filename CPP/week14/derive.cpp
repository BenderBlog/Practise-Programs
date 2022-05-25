#include <iostream>
using namespace std;

/* Define a class as follow:*/
class Base
{
public:
    virtual void iam() { cout << "Base\n"; }
};

/* Derive two classes from Base, and for each define iam()
 * to write out the name of the class. */
class Clapton : public Base
{
public:
    void iam() { cout << "Clapton\n"; }
    Base *father;
};

class Betty : public Base
{
public:
    void iam() { cout << "Betty\n"; }
    Base *father;
};

int main()
{
    /* Create objects of these classes and call iam() for them. */
    Clapton a;
    Betty b;
    a.iam();
    b.iam();
    /* Assign pointers to objects of the derived classes to Base *pointers
     * and call iam() through those pointers.
     * 将派生类的对象的指针分配给Base*指针，并通过这些指针调用iam()。*/
    Base *c = nullptr;
    c = &a;
    c->iam();
    c = &b;
    c->iam();
}