#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <cstdio>

static void identify(Base *p)
{
    if (dynamic_cast<A *>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B *>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C *>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown type" << std::endl;
}

static Base *generate(void)
{
    int random = std::rand() % 3;
    if (random == 0)
        return new A();
    else if (random == 1)
        return new B();
    else
        return new C();
}

int main(void)
{
    std::srand(time(0));
    Base *base = generate();
    identify(base);
    delete base;
    return 0;
}