#include "easyfind.hpp"
#include <vector>
#include <list>

int main(void)
{
    std::vector<int> vec;
    std::list<int> lst;

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
        lst.push_back(i*i);
    }
    
    std::cout << "==========Vector===========" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "==========List=============" << std::endl;
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "============acan===========" << std::endl;

    try {
        std::cout << "Trying to find 5 in vector." << std::endl;
        std::cout << "Vector: " << *easyfind(vec, 5) << std::endl;
        std::cout << "============acan===========" << std::endl;

        std::cout << "Trying to find 16 in list." << std::endl;
        std::cout << "List: " << *easyfind(lst, 16) << std::endl;
        std::cout << "============acan===========" << std::endl;

        std::cout << "Trying to find 15 in vector." << std::endl;
        std::cout << "Vector: " << *easyfind(vec, 15) << std::endl;
        std::cout << "============acan===========" << std::endl;
    } catch (const NotFoundException &e) {
        std::cerr << e.what() << std::endl;
        std::cout << "============acan===========" << std::endl;
        return 1;
    }

    return 0;
}