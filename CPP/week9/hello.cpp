// modify it to produce the following output
// (Do not change main() in any way)
#include <iostream>
/*
std::ostream &operator<<(std::ostream &os, const char (&s)[])
{
    std::operator<<(std::cout, "Initialize\n");
    std::operator<<(std::cout, s);
    std::operator<<(std::cout, "Clean up\n");
    return os;
}
*/
class Whatever
{
public:
    Whatever()
    {
        std::cout << "Initalize" << std::endl;
    }
    ~Whatever()
    {
        std::cout << "Chean up" << std::endl;
    }
};

Whatever a;

int main()
{
    std::cout << "Hello, world!\n";
}